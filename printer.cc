#include "printer.h"
#include <iostream>

using namespace std;

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) :
  	numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {

  	total = 5 + numStudents + numVendingMachines + numCouriers;			// calculate total number of entities

	buff = new char[total]();											// zero initialize char buffer
	val1buff = new int[total];
	val2buff = new int[total];
	fill_n(val1buff, total, -1);										// -1  initialize first val buffer
	fill_n(val2buff, total, -1);										// -1  initialize second val buffer

	// print initial table header
	osacquire(cout) << "Parent\tWATOff\tNames\tTruck\tPlant\t";

	for ( unsigned int i = 0; i < numStudents; i++ ) {
		osacquire(cout) << "Stud" << i << "\t";
	} // for
	for ( unsigned int i = 0; i < numVendingMachines; i++ ) {
		osacquire(cout) << "Mach" << i << "\t";
	} // for
	for ( unsigned int i = 0; i < numCouriers; i++ ) {
		osacquire(cout) << "Cour" << i << "\t";
	} // for
	osacquire(cout) << endl;

	osacquire(cout) << endl;
	for ( unsigned int i = 0; i < total; i++ ) {
		osacquire(cout) << "*******" << "\t";
	} // for
	osacquire(cout) << endl;
} // CXR

void Printer::flush() {
  for ( unsigned int i = 0; i < total; i++ ) {

	osacquire(cout) << buff[i];
	if ( val1buff[i] != -1 ) osacquire(cout) << val1buff[i];
	if ( val2buff[i] != -1 ) osacquire(cout) << "," << val2buff[i];
	osacquire(cout) << "\t";

	// reset values
	buff[i] = '\0';
	val1buff[i] = -1;
	val2buff[i] = -1;
  } // for
  osacquire(cout) << endl;
} // flush


unsigned int Printer::getPos( Kind kind, unsigned int lid ) {
	// return position based on kind and id
	switch ( kind ) {
		case Student:
			return 5 + lid;
		case Vending:
			return 5 + numStudents + lid;
		case Courier:
			return 5 + numStudents + numVendingMachines + lid;
		default:
			return 0;
	} // switch
	return 0;
} //getPos


void Printer::print( Kind kind, char state ) {
	// handle finish
	if ( state == 'F' ) {
		flush();
		for ( unsigned int i = 0; i < total; i++) {
			if ( i == (unsigned int)kind ) {
				osacquire(cout) << state << "\t";
			} else {
				osacquire(cout) << "..." << "\t";
			} // if
		} // for
		osacquire(cout) << endl;
		return;
	} // if

	if ( buff[kind] ) flush();
	buff[kind] = state;
} // print just state


void Printer::print( Kind kind, char state, int value1 ) {
	if ( buff[kind] ) flush();
	buff[kind] = state;
	val1buff[kind] = value1;
} // print state and value


void Printer::print( Kind kind, char state, int value1, int value2 ) {
	if ( buff[kind] ) flush();
	buff[kind] = state;
	val1buff[kind] = value1;
	val2buff[kind] = value2;
} // print state with two values


void Printer::print( Kind kind, unsigned int lid, char state ) {
	unsigned int pos = getPos(kind, lid);				// get position of current entity
	// handle finish
	if ( state == 'F' ) {
		flush();
		for ( unsigned int i = 0; i < total; i++) {
			if ( i == pos ) {
				osacquire(cout) << state << "\t";
			} else {
				osacquire(cout) << "..." << "\t";
			} // if
		} // for
		osacquire(cout) << endl;
		return;
	} // if

	if ( buff[pos] ) flush();
	buff[pos] = state;
} // print state for given id


void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	unsigned int pos = getPos(kind, lid);				// get position of current entity

	if ( buff[pos] ) flush();
	buff[pos] = state;
	val1buff[pos] = value1;
} // print state for given id with value


void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	unsigned int pos = getPos(kind, lid);				// get position of current entity

	if ( buff[pos] ) flush();
	buff[pos] = state;
	val1buff[pos] = value1;
	val2buff[pos] = value2;
} // print state for given id with two values

Printer::~Printer() {
	// cleanup arrays
	delete[] buff;
	delete[] val1buff;
	delete[] val2buff;

	osacquire(cout) << "***********************" << endl;
} // ~Printer