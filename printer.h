#ifndef PRINTER_H
#define PRINTER_H

_Monitor Printer {
	unsigned int numStudents;
	unsigned int numVendingMachines;
	unsigned int numCouriers;
	unsigned int total;
    char* buff;                                 // stores current state
    int* val1buff;                              // stores number associated with current state
    int* val2buff;
    void flush();                               // flushes and prints buffer
    unsigned int getPos( Kind kind, unsigned int lid );	// returns position in buffer
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );

    virtual ~Printer();
};


#endif