#include "bank.h"


Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
	// Initalize accounts to zero
	accounts = new int[numStudents]();

	// Create account locks
	for ( unsigned int i = 0; i < numStudents; i++ ) {
		conds.push_back( new uCondition );
	} // for
} // Bank CXR


void Bank::deposit( unsigned int id, unsigned int amount ) {
	accounts[id] += amount;
	conds[id]->signal();					// Signal to a possible awaiting courier money has been deposited
} // Deposit


void Bank::withdraw( unsigned int id, unsigned int amount ) {
	// Wait for enough money to be deposited by a parent
	while ( accounts[id] < (int)amount ) conds[id]->wait();

	accounts[id] -= amount;

} // Withdraw


Bank::~Bank() {
	// Cleanup accounts and locks
	delete[] accounts;
	while( !conds.empty() ) delete conds.back(), conds.pop_back();
} // Bank DXR
