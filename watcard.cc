#include "watcard.h"
#include <iostream>

using namespace std;

WATCard::WATCard() {
	balance = 0;
}

void WATCard::deposit( unsigned int amount ) {
	balance += amount;
	withdrawCond.signal();
}

void WATCard::withdraw( unsigned int amount ) {
	while ( amount > balance ) {
		osacquire(cout) << "bal: " << balance << "\twdraw: " << amount << endl;
		withdrawCond.wait();
	}
	balance -= amount;
}

unsigned int WATCard::getBalance() {
	return balance;
}