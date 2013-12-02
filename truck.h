#ifndef TRUCK_H
#define TRUCK_H

#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"

_Task Truck {
    void main();

    Printer& printer;
    NameServer& nameServer;
    BottlingPlant& plant;
    unsigned int numVendingMachines, maxStockPerFlavour;
    unsigned int* cargo;
    unsigned int min(unsigned int x, unsigned int y);
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
