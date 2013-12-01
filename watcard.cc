#include "watcard.h"

WATCard::WATCard() {
	balance = 0;
}

void WATCard::deposit( unsigned int amount ) {
	balance += amount;
	withdraw.signal();
}

void WATCard::withdraw( unsigned int amount ) {
	while ( amount < balance ) withdraw.wait();
	balance -= amount;
}

unsigned int WATCard::getBalance() {
	return balance;
}