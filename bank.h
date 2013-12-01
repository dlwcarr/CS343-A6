#include <vector>

_Monitor Bank {
	unsigned int numStudents;
	int* accounts;
	vector<uCondition*> conds;
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );

    virtual ~Bank();
};