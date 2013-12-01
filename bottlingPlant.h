#ifndef BOTTLINGPLANT_H
#define BOTTLINGPLANT_H

#include "printer.h"
#include "nameServer.h"

_Task BottlingPlant {
    void main();
    Printer& printer;
    NameServer& nameServer;
    unsigned int numVendingMachines, maxShippedPerFlavour, maxStockPerFlavour, timeBetweenShipments;
    Truck* truck;
    bool open;
    unsigned int* shipment;
    void produceShipment();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    ~BottlingPlant();
    bool getShipment( unsigned int cargo[] );
};

#endif
