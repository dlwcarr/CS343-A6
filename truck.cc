#include "truck.h"
#include "vendingMachine.h"

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
       unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : printer(prt), nameServer(nameServer),
       plant(plant), numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {
	cargo = new unsigned int [NUM_FLAVOURS];
}

unsigned int Truck::min(unsigned int x, unsigned int y) {
	if (x < y)
		return x;
	return y;
}

void Truck::main() {
	printer.print(Printer::Truck, 'S');

	VendingMachine** machines = nameServer.getMachineList();

	while (true) {
		yield(rng(1, 10)) 			// go to Tom Horton's

		if (plant.getShipment(cargo))
			break;

		int shipmentSize = 0;
		for (unsigned int i = 0; i < NUM_FLAVOURS; i++)
			shipmentSize += cargo[i];
		printer.print(Printer::Truck, 'P', shipmentSize);

		for(unsigned int i = 0; i < numVendingMachines; i++) {
			printer.print(Printer::Truck, 'd', i, shipmentSize);
			
			unsigned int* inventory = machines[i]->inventory();
			unsigned int unfilledCapacity = 0;
			
			for (unsigned int j = 0; j < NUM_FLAVOURS; j++) {
				unsigned int amountToStock = min(cargo[j], maxStockPerFlavour - inventory[j]);
				
				inventory[j] += amountToStock;
				cargo[j] -= amountToStock;
				shipmentSize -= amountToStock;
				unfilledCapacity += maxStockPerFlavour - inventory[j];
			}

			if (unfilledCapacity > 0)
				printer.print(Printer::Truck, 'U', i, unfilledCapacity);

			printer.print(Printer::Truck, 'D', i, shipmentSize);

			machines[i]->restocked();

			if (shipmentSize < 1)
				break;
		}
	}

	delete [] cargo;

	printer.print(Printer::Truck, 'F');
}
