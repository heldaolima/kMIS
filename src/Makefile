CC=g++

all: main

main: graph
	$(CC) -o main.out main.cpp graph.o

graph:
	$(CC) -c graph.cpp

clean:
	rm -f *.o *.out