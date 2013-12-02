#ifndef WATCARD_H
#define WATCARD_H

#include <uFuture.h>

class WATCard {
    WATCard( const WATCard & );            // prevent copying
    WATCard &operator=( const WATCard & );

    unsigned int balance;                   // watcard balance
    uCondition withdrawCond;                // prevents withdrawals if balance is too low

  public:
    WATCard();
    typedef Future_ISM<WATCard *> FWATCard; // future watcard pointer
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
}; // Watcard

#endif