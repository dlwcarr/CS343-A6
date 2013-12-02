#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <vector>
#include <deque>
#include "watcard.h"
#include "printer.h"
#include "bank.h"

_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
        struct Args {
            WATCard* card;
            unsigned int sid;
            unsigned int amount;
            Args ( unsigned int sid, unsigned int amount, WATCard *card ) :
                card(card), sid(sid), amount(amount) {}
        };

        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };

    _Task Courier {
        Printer &prt;
        Bank &bank;
        WATCardOffice &cardOffice;
        unsigned int id;

        void main();

      public:
        Courier( Printer &prt, Bank &bank, WATCardOffice &cardOffice, unsigned int id );
    };

    Printer &prt;
    Bank &bank;
    unsigned int numCouriers;
    std::vector<Courier*> couriers;
    std::deque<Job*> jobs;

    void main();
  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();

    virtual ~WATCardOffice();
};

#endif
