#include "bottlingPlant.h"

using namespace std;

extern MPRNG rng;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
         unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) 
		: printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour),
		maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments), open(true) 	{

	shipment = new unsigned int [NUM_FLAVOURS];
}

BottlingPlant::~BottlingPlant() {
	delete [] shipment;
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (!open)
		return true;



	return false;
}

void BottlingPlant::produceShipment() {
	for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {

	}
}

void BottlingPlant::main() {
	truck = new Truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);


}
