CC=g++
DEPENDENCIES= globals.cpp helpers/*.cpp data_structures/*.cpp heuristics/*.cpp heuristics/grasp/*.cpp
ILS_DEPENDENCIES=globals.cpp data_structures/*.cpp heuristics/ils.cpp heuristics/greedy.cpp heuristics/local_search.cpp heuristics/path_relinking.cpp
FLAGS=-g -O0

ils: clean dependencies
	$(CC) $(FLAGS) -o main.out main.cpp *.o

dependencies:
	$(CC) -c $(DEPENDENCIES) 

clean:
	rm -f *.o *.out
