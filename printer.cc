#include "printer.h"
#include <iostream>

using namespace std;

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) :
  	numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {

  	total = 5 + numStudents + numVendingMachines + numCouriers;

	buff = new char[total]();
	val1buff = new int[total]();
	val2buff = new int[total]();

	cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";

	// print initial table header
	for ( unsigned int i = 0; i < numStudents; i++ ) {
		cout << "Stud" << i << "\t";
	} // for
	for ( unsigned int i = 0; i < numVendingMachines; i++ ) {
		cout << "Mach" << i << "\t";
	} // for
	for ( unsigned int i = 0; i < numCouriers; i++ ) {
		cout << "Cour" << i << "\t";
	} // for
	cout << endl;

	cout << endl;
	for ( unsigned int i = 0; i < total; i++ ) {
		cout << "*******" << "\t";
	} // for
	cout << endl;
} // CXR

void Printer::flush() {
  for ( unsigned int i = 0; i < total; i++ ) {

	cout << buff[i];
	if ( val1buff[i] != 0 ) cout << val1buff[i];
	if ( val2buff[i] != 0 ) cout << "," << val2buff[i];
	cout << "\t";

	buff[i] = '\0';
	val1buff[i] = 0;
	val2buff[i] = 0;
  } // for
  cout << endl;
} // flush


unsigned int Printer::getPos( Kind kind, unsigned int lid ) {
	switch ( kind ) {
		case Student:
			return 5 + lid;
		case Vending:
			return 5 + numStudents + lid;
		case Courier:
			return 5 + numStudents + numVendingMachines + lid;
	}
}


void Printer::print( Kind kind, char state ) {
	if ( state == 'F' ) {
		flush();
		for ( unsigned int i = 0; i < total; i++) {
			if ( i == kind ) {
				cout << state << "\t";
			} else {
				cout << "..." << "\t";
			}
		}
		cout << endl;
		return;
	}

	if ( buff[kind] ) flush();
	buff[kind] = state;
}


void Printer::print( Kind kind, char state, int value1 ) {
	if ( buff[kind] ) flush();
	buff[kind] = state;
	val1buff[kind] = value1;
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
	if ( buff[kind] ) flush();
	buff[kind] = state;
	val1buff[kind] = value1;
	val2buff[kind] = value2;
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
	unsigned int pos = getPos(kind, lid);

	if ( state == 'F' ) {
		flush();
		for ( unsigned int i = 0; i < total; i++) {
			if ( i == pos ) {
				cout << state << "\t";
			} else {
				cout << "..." << "\t";
			}
		}
		cout << endl;
		return;
	}

	if ( buff[pos] ) flush();
	buff[pos] = state;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	unsigned int pos = getPos(kind, lid);

	if ( buff[pos] ) flush();
	buff[pos] = state;
	val1buff[pos] = value1;
}
void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	unsigned int pos = getPos(kind, lid);

	if ( buff[pos] ) flush();
	buff[pos] = state;
	val1buff[pos] = value1;
	val2buff[pos] = value2;
}

Printer::~Printer() {
	delete[] buff;
	delete[] val1buff;
	delete[] val2buff;

	cout << "***********************" << endl;
} // ~Printer