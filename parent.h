#ifndef PARENT_H
#define PARENT_H

#include "printer.h"
#include "bank.h"

_Task Parent {
	Printer &prt;
	Bank &bank;
	unsigned int numStudents;			// number of students
	unsigned int parentalDelay;			// delay between donations
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
}; // Parent

#endif
