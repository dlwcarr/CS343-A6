#include "watcard.h"

using namespace std;

WATCard::WATCard() {
	balance = 0;
}

void WATCard::deposit( unsigned int amount ) {
	balance += amount;
	withdrawCond.signal();
}

void WATCard::withdraw( unsigned int amount ) {
	while ( amount > balance ) withdrawCond.wait();
	balance -= amount;
}

unsigned int WATCard::getBalance() {
	return balance;
}