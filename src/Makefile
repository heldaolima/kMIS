CC=g++
HEADERS= graph.cpp element.cpp solution.cpp build_entry.cpp

all: main

main: dependencies
	clear
	$(CC) -o main.out main.cpp *.o
	./main.out

dependencies:
	$(CC) -c $(HEADERS)

clean:
	rm -f *.o *.out