_Task Parent {
	Printer &prt;
	Bank &bank;
	unsigned int numStudents;
	unsigned int parentalDelay;
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
    	prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}
};