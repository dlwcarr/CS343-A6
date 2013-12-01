#ifndef NAMESERVER_H
#define NAMESERVER_H

#include <uC++.h>
#include "printer.h"
#include "vendingMachine.h"

_Task NameServer {
    void main();
    Printer& printer;
    unsigned int numVendingMachines, numStudents;
    VendingMachine** machineList;					// list of machines in the order they registered (not by machine->id)
    unsigned int lastMachine;						// holds the location of the last registered machine + 1
    unsigned int* studentsMachine;					// machines assigned to each student
    uCondition machineNotRegistered;				// blocks a student if they request an unregistered machine
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
