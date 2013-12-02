#include <uC++.h>
#include <iostream>
#include "nameServer.h"

using namespace std;

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : printer(prt), 
			numVendingMachines(numVendingMachines), numStudents(numStudents), lastMachine(0), machineNotRegistered(numVendingMachines) {
	machineList = new VendingMachine* [numVendingMachines];
	studentsMachine = new unsigned int [numStudents];
	
	for (unsigned int i = 0; i < machineNotRegistered.size(); i++)
		machineNotRegistered[i] = new uCondition();
}

NameServer::~NameServer() {
	delete [] machineList;
	delete [] studentsMachine;

	for (unsigned int i = 0; i < machineNotRegistered.size(); i++)
		delete machineNotRegistered[i];
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
	printer.print(Printer::NameServer, 'R', lastMachine);

	machineList[lastMachine] = vendingmachine;

	// unblock students waiting on this machine
	while (!machineNotRegistered[lastMachine]->empty())
		machineNotRegistered[lastMachine]->signal();

	lastMachine += 1;

	// unblock truck once all machine are registered
	if (lastMachine >= numVendingMachines)
		truckLock.signal();
}

VendingMachine* NameServer::getMachine( unsigned int id ) {
	// block if machine hasn't been registered yet
	if (studentsMachine[id] >= lastMachine)
		machineNotRegistered[studentsMachine[id]]->wait();

	VendingMachine* machine = machineList[studentsMachine[id]];
	printer.print(Printer::NameServer, 'N', id, studentsMachine[id]);

	studentsMachine[id] = (studentsMachine[id] + 1) % numVendingMachines;
	return machine;
}

VendingMachine** NameServer::getMachineList() {
	// block until all vending machines are registered
	if (lastMachine < numVendingMachines)
		truckLock.wait();

	return machineList;
}

void NameServer::main() {
	printer.print(Printer::NameServer, 'S');

	// assign initial vending machines to students
	for (unsigned int i = 0; i < numStudents; i++) {
		studentsMachine[i] = i % numVendingMachines;
	}

	while(true) {
		_Accept(~NameServer) {
			break;
		}
		or _Accept(VMregister, getMachine, getMachineList);
	}

	printer.print(Printer::NameServer, 'F');
}
