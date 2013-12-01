#include "nameServer.h"

using namespace std;

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : printer(prt), 
			numVendingMachines(numVendingMachines), numStudents(numStudents), lastMachine(0) {
	machineList = new VendingMachine* [numVendingMachines];
	studentsMachine = new unsigned int* [numStudents];
}

NameServer::~NameServer() {
	delete [] machineList;
	delete [] studentsMachine;
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
	printer.print(Printer::NameServer, lastMachine, 'R');

	machineList[lastMachine] = vendingmachine;
	lastMachine += 1;

	// let students unblock when a new machine is registered
	while (!machineNotRegistered.empty())
		machineNotRegistered.signal();
}

VendingMachine* NameServer::getMachine( unsigned int id ) {
	// block if machine hasn't been registered yet
	while (studentsMachine[id] >= lastMachine)
		machineNotRegistered.wait();

	VendingMachine* machine = machineList[studentsMachine[id]];
	printer.print(Printer::NameServer, id, 'N', studentsMachine[id]);

	studentsMachine[id] = (studentsMachine[id] + 1) % numVendingMachines;
	return machine;
}

VendingMachine** NameServer::getMachineList() {
	// block until all vending machines are registered
	while (lastMachine < numVendingMachines)
		machineNotRegistered.wait();

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
		} _Else {}
	}

	printer.print(Printer::NameServer, 'F');
}
