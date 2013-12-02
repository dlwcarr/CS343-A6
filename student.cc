#include "student.h"
#include "MPRNG.h"
#include "vendingMachine.h"

extern MPRNG rng;

void Student::main() {
	int purchases = rng(1, maxPurchases);
	VendingMachine::Flavours fav = static_cast<VendingMachine::Flavours>(rng(0, 3));

	prt.print( Printer::Student, id, 'S', fav, purchases );

	WATCard* realCard = new WATCard;

	WATCard::FWATCard futureCard = cardOffice.create(id, 5);

	VendingMachine* vend = nameServer.getMachine( id );
	prt.print( Printer::Student, id, 'V', vend->getId() );

	while ( purchases > 0 ) {
		yield(rng(1, 10));

		while ( true ) {
			realCard = futureCard();

			try {
				VendingMachine::Status status = vend->buy(fav, *realCard);

				if ( status == VendingMachine::BUY ) {
					--purchases;
					prt.print( Printer::Student, id, 'B', realCard->getBalance() );
					break;
				} else if ( status == VendingMachine::FUNDS ) {
					futureCard = cardOffice.transfer(id, 5 + vend->cost(), realCard);
				} else if ( status == VendingMachine::STOCK ) {
					prt.print( Printer::Student, id, 'V', vend->getId() );
					vend = nameServer.getMachine( id );
				}
			} catch ( WATCardOffice::Lost ) {
				prt.print( Printer::Student, id, 'L' );
				delete realCard;
				WATCard* realCard = new WATCard;
				WATCard::FWATCard futureCard = cardOffice.create(id, 5);
			}
		}
	}

	delete realCard;
	prt.print( Printer::Student, id, 'F' );
}

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
    	unsigned int maxPurchases ) : prt(prt), nameServer(nameServer), cardOffice(cardOffice),
			id(id), maxPurchases(maxPurchases) {}