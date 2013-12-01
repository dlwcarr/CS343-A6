#include <uC++.h>
#include <iostream>
#include <unistd.h>
#include "MPRNG.h"
#include "config.h"

using namespace std;

MPRNG rng;

void printUsage(char *argv) {
	osacquire(cout) << "Usage: " << argv << " [ config-file [ random-seed (> 0) ] ]" << endl;
}

void uMain::main() {
	int seed = getpid();
	char* filename = "soda.config";

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
	processConfigFile(filename, config);

	osacquire(cout) << "sodaCost " << config.sodaCost << endl
					<< "numStudents " << config.numStudents << endl
					<< "maxPurchases " << config.maxPurchases << endl
					<< "numVendingMachines " << config.numVendingMachines << endl
					<< "maxStockPerFlavour " << config.maxStockPerFlavour << endl
					<< "maxShipperPerFlavour " << config.maxShipperPerFlavour << endl
					<< "timeBetweenShipments " << config.timeBetweenShipments << endl
					<< "parentalDelay " << config.parentalDelay << endl
					<< "numCouriers " << config.numCouriers << endl;

}
