#include "watcardOffice.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG rng;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
	prt(prt), bank(bank), numCouriers(numCouriers) {

		for ( unsigned int i = 0; i < numCouriers; i ++ ) {
			couriers.push_back( new Courier( prt, bank, *this, i ) );
		}
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	Job::Args args( sid, amount, new WATCard() );
	Job* job = new Job( args );
	jobs.push_back(job);
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	Job::Args args( sid, amount, card );
	Job* job = new Job( args );
	jobs.push_back(job);
	return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	return jobs.front();
}

void WATCardOffice::main() {
	prt.print( Printer::WATCardOffice, 'S' );

	while ( true ) {
		_When( !jobs.empty() ) _Accept( requestWork ) {
			jobs.pop_front();
			prt.print( Printer::WATCardOffice, 'W' );
		} or _Accept( create ) {
			prt.print( Printer::WATCardOffice, 'C', jobs.back()->args.sid, jobs.back()->args.amount );
		} or _Accept( transfer ) {
			prt.print( Printer::WATCardOffice, 'T', jobs.back()->args.sid, jobs.back()->args.amount );
		} or _Accept( ~WATCardOffice ) {
			break;
		}
	}
}

WATCardOffice::~WATCardOffice() {
	while(!couriers.empty()) delete couriers.back(), couriers.pop_back();
	prt.print( Printer::WATCardOffice, 'F' );
}

void WATCardOffice::Courier::main() {
	prt.print( Printer::Courier, id, 'S' );

	while ( true ) {
		_Accept(~Courier) {
			break;
		} _Else {
			WATCardOffice::Job* job = cardOffice.requestWork();

			prt.print( Printer::Courier, id, 't', job->args.sid, job->args.amount );
			bank.withdraw( job->args.sid, job->args.amount );
			job->args.card->deposit( job->args.amount );
			prt.print( Printer::Courier, id, 'T', job->args.sid, job->args.amount );

			if ( rng(5) == 0 ) {
				delete job->args.card;
				job->result.exception( new WATCardOffice::Lost() );
			} else {
				job->result.delivery( job->args.card );
			}

			delete job;
		}
	}

	prt.print( Printer::Courier, id, 'F' );

}

WATCardOffice::Courier::Courier( Printer &prt, Bank &bank, WATCardOffice &cardOffice, unsigned int id ) :
	prt(prt), bank(bank), cardOffice(cardOffice), id(id) {}