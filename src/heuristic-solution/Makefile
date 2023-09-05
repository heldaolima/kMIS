CC=g++
DEPENDENCIES= graph.cpp globals.cpp data_structures/*.cpp heuristics/*.cpp

all: main

main: dependencies
	$(CC) -o main.out main.cpp *.o

dependencies:
	$(CC) -c $(DEPENDENCIES) 

clean:
	rm -f *.o *.out