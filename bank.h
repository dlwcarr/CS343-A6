#ifndef BANK_H
#define BANK_H

#include <vector>

_Monitor Bank {
	unsigned int numStudents;			// number of students
	int* accounts;						// student accounts
	std::vector<uCondition*> conds;		// locks for withdrawal when balance is less than withdrawal amount
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );

    virtual ~Bank();
}; // Bank

#endif
