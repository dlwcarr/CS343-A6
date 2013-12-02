#include "watcardOffice.h"
#include "MPRNG.h"

using namespace std;

extern MPRNG rng;


WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
	prt(prt), bank(bank), numCouriers(numCouriers) {
		// Create pool of couriers
		for ( unsigned int i = 0; i < numCouriers; i ++ ) {
			couriers.push_back( new Courier( prt, bank, *this, i ) );
		} // for
} // WATCardOffice CXR


WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	// Create job with new watcard
	Job::Args args( sid, amount, new WATCard() );
	Job* job = new Job( args );
	jobs.push_back(job);

	prt.print( Printer::WATCardOffice, 'C', jobs.back()->args.sid, jobs.back()->args.amount );
	return job->result;
} // create


WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	// Create job with current card
	Job::Args args( sid, amount, card );
	Job* job = new Job( args );
	jobs.push_back(job);

	prt.print( Printer::WATCardOffice, 'T', jobs.back()->args.sid, jobs.back()->args.amount );
	return job->result;
} // transfer


WATCardOffice::Job* WATCardOffice::requestWork() {
	if ( jobs.empty() ) return NULL;		// tells courier it is done
	return jobs.front();					// give courier job
} // requestWork


void WATCardOffice::main() {
	prt.print( Printer::WATCardOffice, 'S' );

	while ( true ) {
		_When( !jobs.empty() ) _Accept( requestWork ) {
			jobs.pop_front();					// job is complete, remove from list
			prt.print( Printer::WATCardOffice, 'W' );
		} or _Accept( create, transfer ) {
		} or _Accept( ~WATCardOffice ) {
			// Signal to couriers that there are no more jobs (create dummy jobs)
			for ( unsigned int i = 0; i < numCouriers; i++ ) _Accept( requestWork );
			break;
		} // _Accept
	} // while
} // WATCardOffice main


WATCardOffice::~WATCardOffice() {
	while(!couriers.empty()) delete couriers.back(), couriers.pop_back();
	prt.print( Printer::WATCardOffice, 'F' );
} // WATCardOffice DXR


void WATCardOffice::Courier::main() {
	prt.print( Printer::Courier, id, 'S' );

	while ( true ) {
		WATCardOffice::Job* job = cardOffice.requestWork();			// get job

		if ( job == NULL ) break;									// work is done

		prt.print( Printer::Courier, id, 't', job->args.sid, job->args.amount );
		bank.withdraw( job->args.sid, job->args.amount );
		job->args.card->deposit( job->args.amount );
		prt.print( Printer::Courier, id, 'T', job->args.sid, job->args.amount );

		// 1 in 6 chance card is lost
		if ( rng(5) == 0 ) {
			delete job->args.card;			// delete old watcard
			job->result.exception( new WATCardOffice::Lost() );
		} else {
			job->result.delivery( job->args.card );
		} // if

		delete job;				// cleanup job
	} // while

	prt.print( Printer::Courier, id, 'F' );

} // Courier main

WATCardOffice::Courier::Courier( Printer &prt, Bank &bank, WATCardOffice &cardOffice, unsigned int id ) :
	prt(prt), bank(bank), cardOffice(cardOffice), id(id) {}