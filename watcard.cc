#include "watcard.h"

using namespace std;

WATCard::WATCard() {
	balance = 0;										// initialize balance to 0
} // CXR


void WATCard::deposit( unsigned int amount ) {
	balance += amount;
	withdrawCond.signal();								// signal that there may be enough funds to withdraw now
} // deposit


void WATCard::withdraw( unsigned int amount ) {
	while ( amount > balance ) withdrawCond.wait();		// wait until there are enough funds to withdraw
	balance -= amount;
} // withdraw


unsigned int WATCard::getBalance() {
	return balance;
} // getBalance