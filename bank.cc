#include "bank.h"

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
	accounts = new int[numStudents]();

	for ( unsigned int i = 0; i < numStudents; i++ ) {
		conds.push_back(new uCondition);
	}
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
	accounts[id] += amount;
	conds[id]->signal();
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	while ( accounts[id] < (int)amount ) {
		conds[id]->wait();
	}

	accounts[id] -= amount;

}

Bank::~Bank() {
	delete[] accounts;
	while(!conds.empty()) delete conds.back(), conds.pop_back();
}
