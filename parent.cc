#include "parent.h"
#include "printer.h"
#include "MPRNG.h"

extern MPRNG rng;

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) 
				: prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main() {

	prt.print(Printer::Parent, 'S');

	while ( true ) {
		_Accept(~Parent) {
			break;
		} _Else {
			int money = rng(1,3);
			int student = rng(numStudents - 1);
			yield(parentalDelay);

			bank.deposit(student, money);

			prt.print(Printer::Parent, 'D', student, money);
		}
	}

	prt.print(Printer::Parent, 'F');

}