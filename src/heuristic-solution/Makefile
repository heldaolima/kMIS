CC=g++
DEPENDENCIES= globals.cpp heuristic_factory.cpp helpers/*.cpp data_structures/*.cpp heuristics/*.cpp heuristics/grasp/*.cpp
FLAGS=-g -lm -O0

ils: clean dependencies
	$(CC) $(FLAGS) -o main.out main.cpp *.o

pre: clean dependencies
	$(CC) $(FLAGS) -o pre.out preliminaries.cpp *.o

dependencies:
	$(CC) -c $(DEPENDENCIES) 

clean:
	rm -f *.o *.out
