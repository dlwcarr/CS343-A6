#include <uC++.h>

#include "student.h"
#include "MPRNG.h"
#include "vendingMachine.h"
#include <iostream>

using namespace std;

extern MPRNG rng;

void Student::main() {
	int purchases = rng(1, maxPurchases);
	VendingMachine::Flavours fav = static_cast<VendingMachine::Flavours>(rng(0, 3));

	prt.print( Printer::Student, id, 'S', fav, purchases );

	WATCard::FWATCard futureCard = cardOffice.create(id, 5);

	VendingMachine* vend = nameServer.getMachine( id );
	prt.print( Printer::Student, id, 'V', vend->getId() );

	while ( purchases > 0 ) {
		yield(rng(1, 10));

		while ( true ) {
			try {
				VendingMachine::Status status = vend->buy(fav, *futureCard());
				if ( status == VendingMachine::BUY ) {
					--purchases;
					prt.print( Printer::Student, id, 'B', futureCard()->getBalance() );
					break;
				} else if ( status == VendingMachine::FUNDS ) {
					futureCard = cardOffice.transfer(id, 5 + vend->cost(), futureCard);
				} else if ( status == VendingMachine::STOCK ) {
					prt.print( Printer::Student, id, 'V', vend->getId() );
					vend = nameServer.getMachine( id );
				}
			} catch ( WATCardOffice::Lost ) {
				prt.print( Printer::Student, id, 'L' );
				futureCard = cardOffice.create(id, 5);
			}
		}
	}

	prt.print( Printer::Student, id, 'F' );
}

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
    	unsigned int maxPurchases ) : prt(prt), nameServer(nameServer), cardOffice(cardOffice),
			id(id), maxPurchases(maxPurchases) {}