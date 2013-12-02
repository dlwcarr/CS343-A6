#ifndef STUDENT_H
#define STUDENT_H

#include "printer.h"
#include "nameServer.h"
#include "watcardOffice.h"

_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	unsigned int id;					// id of student
	unsigned int maxPurchases;			// maximum number of puchases a student can make

    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );

};	// Student

#endif