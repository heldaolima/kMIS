CC=g++
HEADERS= graph.cpp globals.cpp data_structures/*.cpp heuristics/*.cpp

all: main

main: dependencies
	clear
	$(CC) -o main.out main.cpp *.o
	./main.out

dependencies:
	$(CC) -c $(HEADERS)

clean:
	rm -f *.o *.out