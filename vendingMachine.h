#include <uC++.h>
#include "printer.h"
#include "nameServer.h"
#include "watcard.h"
#include <vector>

_Task VendingMachine {
    void main();

    Printer& printer;
    NamerServer& nameServer;
    unsigned int id, sodaCost, maxStockPerFlavour;
    const unsigned int NUM_FLAVOURS = 4;    // keep up to date after changing Flavours enum
    unsigned int* stock;
    bool stocking;

  public:
    enum Flavours { BLACK_CHERRY, CREAM_SODA, ROOT_BEER, LIME };                 // flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };     // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};