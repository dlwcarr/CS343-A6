#ifndef STUDENT_H
#define STUDENT_H

_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	unsigned int id;
	unsigned int maxPurchases;

    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );

    virtual ~Student();
};

#endif