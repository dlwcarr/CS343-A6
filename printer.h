#ifndef PRINTER_H
#define PRINTER_H

_Monitor Printer {
	unsigned int numStudents;                  // number of students
	unsigned int numVendingMachines;           // number of vending machines
	unsigned int numCouriers;                  // number of couriers
	unsigned int total;                        // total number of entites
    char* buff;                                // stores current state
    int* val1buff;                             // stores number associated with current state
    int* val2buff;                             // stores second number associated with current state
    void flush();                              // flushes and prints buffer
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
  private:
    unsigned int getPos( Kind kind, unsigned int lid ); // returns position in buffer
}; // Printer


#endif

