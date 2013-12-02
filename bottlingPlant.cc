#include "bottlingPlant.h"
#include "MPRNG.h"

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
	delete truck;
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
	if (!open)
		return true;

	for(unsigned int i = 0; i < NUM_FLAVOURS; i++)
		cargo[i] = shipment[i];

	printer.print(Printer::BottlingPlant, 'P');

	return false;
}

void BottlingPlant::produceShipment() {
	int shipmentSize = 0;
	for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
		shipment[id] = rng(maxShippedPerFlavour);
		shipmentSize += shipment[id];
	}
	printer.print(Printer::BottlingPlant, 'G', shipmentSize);
}

void BottlingPlant::main() {
	printer.print(Printer::BottlingPlant, 'S');

	truck = new Truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

	yield(timeBetweenShipments);
	produceShipment();

	while(true) {
		_Accept(~BottlingPlant) {
			break;
		}
		or _Accept(getShipment) {
			yield(timeBetweenShipments);
			produceShipment();
		}
	}

	printer.print(Printer::BottlingPlant, 'F');
}
