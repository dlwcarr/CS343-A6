CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS5 = bank.o bottlingPlant.o nameServer.o parent.o printer.o student.o truck.o vendingMachine.o watcard.o watcardOffice.o # list of object files
EXEC5 = soda

OBJECTS = ${OBJECTS5}
DEPENDS = ${OBJECTS:.o=.d}
EXECS = ${EXEC5}

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

${EXEC5} : ${OBJECTS5}
	${CXX} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC0} ${EXEC00} ${EXECS}
