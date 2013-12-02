#include <uC++.h>
#include "student.h"
#include "MPRNG.h"
#include "vendingMachine.h"
#include <iostream>

using namespace std;

extern MPRNG rng;


void Student::main() {
	int purchases = rng(1, maxPurchases);						// number of puchases the student will make

	VendingMachine::Flavours fav =
		static_cast<VendingMachine::Flavours>(rng(0, 3)); 		// Cast favourite flavour to enum

	prt.print( Printer::Student, id, 'S', fav, purchases );

	WATCard::FWATCard futureCard = cardOffice.create(id, 5);	// Create watcard

	VendingMachine* vend = nameServer.getMachine( id );			// Get vending machine
	prt.print( Printer::Student, id, 'V', vend->getId() );

	while ( purchases > 0 ) {
		// Wait
		yield(rng(1, 10));

		while ( true ) {
			try {
				VendingMachine::Status status = vend->buy(fav, *futureCard());		// Attempt purchase
				if ( status == VendingMachine::BUY ) {
					// Successful purchase, one less to buy
					--purchases;
					prt.print( Printer::Student, id, 'B', futureCard()->getBalance() );
					break;
				} else if ( status == VendingMachine::FUNDS ) {
					// Acquire more funds
					futureCard = cardOffice.transfer(id, 5 + vend->cost(), futureCard);
				} else if ( status == VendingMachine::STOCK ) {
					// Get a new vending machine
					vend = nameServer.getMachine( id );
					prt.print( Printer::Student, id, 'V', vend->getId() );
					yield(rng(1, 10));
				} // if
			} catch ( WATCardOffice::Lost ) {
				// Get a new watcard because couriers lost current one
				prt.print( Printer::Student, id, 'L' );
				futureCard = cardOffice.create(id, 5);
			} // try/catch
		} // while
	} // while

	delete futureCard();							// cleanup futureCard
	prt.print( Printer::Student, id, 'F' );
} // main


Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
    	unsigned int maxPurchases ) : prt(prt), nameServer(nameServer), cardOffice(cardOffice),
			id(id), maxPurchases(maxPurchases) {}