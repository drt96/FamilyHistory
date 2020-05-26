###############################################################
# Program:
#     Week 13, GENEALOGY
#     Brother Ercanbrack, CS235
# Author:
#	Daniel Thomson
# Summary:
#   The purpose of this assignment is to combine the
#	knowledge you have accumulated this semester to solve a
#	problem
# Time:
#     25 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o individual.o
	g++ -o a.out week13.o individual.o -std=c++11 
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o     : the driver program
#	   individual.o : Data within the records
##############################################################
week13.o: individual.h list.h bnode.h merge.h week13.cpp
	g++ -c week13.cpp -std=c++11

individual.o: individual.h individual.cpp
	g++ -c individual.cpp -std=c++11

##############################################################
# Makes clean 
##############################################################
clean:
	rm a.out *.o *.tar

all : a.out