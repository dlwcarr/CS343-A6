#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include <uC++.h>
#include "printer.h"
#include "watcard.h"
#include "nameServer.h"

_Task VendingMachine {
    void main();

    Printer& printer;
    NameServer& nameServer;
    unsigned int id, sodaCost, maxStockPerFlavour;
    unsigned int* stock;
    bool stocking;

  public:
    // Update makefile NUM_FLAVOURS after changing Flavours enum
    enum Flavours { BLACK_CHERRY = 0, CREAM_SODA, ROOT_BEER, LIME};                 // flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
    ~VendingMachine();
};

#endif
