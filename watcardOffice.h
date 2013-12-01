#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
        struct Args {
            WATCard* card;
            unsigned int sid;
            unsigned int amount;
            Args ( unsigned int sid, unsigned int amount, WATCard *card ) :
                sid(sid), amount(amount), card(card) {}
        };

        Args args;                         // call arguments (YOU DEFINE "Args")
        FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };
    _Task Courier { ... };                 // communicates with bank

    Printer &prt;
    Banke &bank;
    unsigned int numCouriers;
    vector<Job*> jobs;

    void main();
  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    FWATCard create( unsigned int sid, unsigned int amount );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();

    virtual ~WATCardOffice();
};

#endif
