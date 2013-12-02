#include <uC++.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include "MPRNG.h"
#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watcardOffice.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "student.h"
#include "bottlingPlant.h"

using namespace std;

MPRNG rng;

void printUsage(char *argv) {
	osacquire(cout) << "Usage: " << argv << " [ config-file [ random-seed (> 0) ] ]" << endl;
}

void uMain::main() {
	int seed = getpid();
	string filename = "soda.config";

	if (argc > 3) {
		printUsage(argv[0]);
		return;
	}

	if (argc > 1) filename = argv[1];
	if (argc > 2) seed = atoi(argv[2]);

	if (seed <= 0) {
		printUsage(argv[0]);
		return;
	}

	rng.seed(seed);

	ConfigParms config;
	processConfigFile(filename.c_str(), config);

	// osacquire(cout) << "sodaCost " << config.sodaCost << endl
	// 				<< "numStudents " << config.numStudents << endl
	// 				<< "maxPurchases " << config.maxPurchases << endl
	// 				<< "numVendingMachines " << config.numVendingMachines << endl
	// 				<< "maxStockPerFlavour " << config.maxStockPerFlavour << endl
	// 				<< "maxShippedPerFlavour " << config.maxShippedPerFlavour << endl
	// 				<< "timeBetweenShipments " << config.timeBetweenShipments << endl
	// 				<< "parentalDelay " << config.parentalDelay << endl
	// 				<< "numCouriers " << config.numCouriers << endl;

	vector<VendingMachine*> machines(config.numVendingMachines);
	vector<Student*> students(config.numStudents);

	Printer* printer = new Printer(config.numStudents, config.numVendingMachines, config.numCouriers);
	Bank* bank = new Bank(config.numStudents);
	Parent* parent = new Parent(*printer, *bank, config.numStudents, config.parentalDelay);
	WATCardOffice* office = new WATCardOffice(*printer, *bank, config.numCouriers);
	NameServer* nameServer = new NameServer(*printer, config.numVendingMachines, config.numStudents);

	for(unsigned int i = 0; i < machines.size(); i++)
		machines[i] = new VendingMachine(*printer, *nameServer, i, config.sodaCost, config.maxStockPerFlavour);

	BottlingPlant* plant = new BottlingPlant(*printer, *nameServer, config.numVendingMachines, config.maxShippedPerFlavour, config.maxStockPerFlavour, config.timeBetweenShipments);

	for(unsigned int i = 0; i < students.size(); i++)
		students[i] = new Student(*printer, *nameServer, *office, i, config.maxPurchases);


	for (unsigned int i = 0; i < students.size(); i++)
		delete students[i];

	delete plant;
	delete nameServer;	

	for (unsigned int i = 0; i < machines.size(); i++) 
		delete machines[i];

	// delete nameServer;
	delete parent;
	delete office;
	delete bank;
	delete printer;
}
