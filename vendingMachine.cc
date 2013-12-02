#include "vendingMachine.h"

using namespace std;

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                unsigned int maxStockPerFlavour ) : printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost),
                maxStockPerFlavour(maxStockPerFlavour), stocking(false) {
	stock = new unsigned int [NUM_FLAVOURS];
}

VendingMachine::~VendingMachine() {
	delete [] stock;
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card ) {
	// need to figure out precedence of STOCK vs FUNDS
	if (card.getBalance() < sodaCost)
		return FUNDS;
	if (stock[flavour] == 0)
		return STOCK;

	card.withdraw(sodaCost);
	stock[flavour] -= 1;

	printer.print(Printer::Vending, id, 'B', flavour, stock[flavour]);

	return BUY;
}

unsigned int* VendingMachine::inventory() {
	printer.print(Printer::Vending, id, 'r');
	stocking = true;
	return stock;
}

void VendingMachine::restocked() {
	stocking = false;
	printer.print(Printer::Vending, id, 'R');
}

_Nomutex unsigned int VendingMachine::cost() {
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
	return id;
}

void VendingMachine::main() {
	printer.print(Printer::Vending, id, 'S', sodaCost);

	nameServer.VMregister(this);

	while(true) {
		_Accept(~VendingMachine) {
			break;
		}
		or _When(stocking) _Accept(restocked) {

		} or _Accept(buy, inventory) {}
	}

	printer.print(Printer::Vending, id, 'F');
}
