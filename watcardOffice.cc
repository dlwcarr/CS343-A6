#include "watcardOffice.h"

extern MPRNG rng;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
	prt(prt), bank(bank), numCouriers(numCouriers) {

}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {

}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {

}

WATCardOffice::Job* WATCardOffice::requestWork() {

}

WATCardOffice::~WATCardOffice() {

}

void WATCardOffice::Courier::main() {
	prt.print( Printer::Courier, id, 'S' );

	while ( true ) {
		_Accept(~Courier) {
			break;
		} _Else {
			WATCardOffice::Job* job = cardOffice.requestWork();

			prt.print( Printer::Courier, id, 't', job->args.sid, jobs->args.amount );
			bank.withdraw( job->args.sid, jobs->args.amount );
			job->args.card->deposit( jobs->args.amount );
			prt.print( Printer::Courier, id, 'T', job->args.sid, jobs->args.amount );

			if ( !rng(0,5) ) {
				job->result.exception( new WATCardOffice::Lost() );
			} else {
				job->result.delivery( jobs->args.card );
			}

			delete job;
		}
	}

	prt.print( Printer::Courier, id, 'F' );

}

WATCardOffice::Courier::Courier( Printer &prt, Bank &bank, WATCardOffice &cardOffice, unsigned int id ) :
	prt(prt), bank(bank), cardOffice(cardOffice), id(id) {}