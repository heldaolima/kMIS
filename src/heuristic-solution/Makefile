CC=g++
BASE_FLAGS=-g -lm -O3
FLAGS=$(BASE_FLAGS) $(EXTRA_FLAGS)

SOURCES = $(wildcard *.cpp) $(wildcard helpers/*.cpp) \
						$(wildcard data_structures/*.cpp) \
						$(wildcard heuristics/*.cpp) \
						$(wildcard heuristics/grasp/*.cpp) \
						$(wildcard heuristics/ils/*.cpp) \
						$(wildcard heuristics/greedy/*.cpp) \
						$(wildcard heuristics/ls_strategies/*.cpp) \
						$(wildcard heuristics/ls_strategies/factories/*.cpp) \
						$(wildcard heuristics/ls_strategies/swap1/*.cpp) \
						$(wildcard heuristics/ls_strategies/swap2/*.cpp) \
						$(wildcard heuristics/stop_strategies/*.cpp) \
						$(wildcard heuristics/perturb_strategies/*.cpp) \
						$(wildcard heuristics/perturb_strategies/get_number_strategies/*.cpp) \
						$(wildcard heuristics/perturb_strategies/factories/*.cpp) \
						$(wildcard heuristics/acceptance_criteria_strategies/*.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: main.out

main.out: $(OBJECTS)
	$(CC) $(FLAGS) -o $@ $^

run_standard:
	./main.out -d -f results_ils.csv --swap2=no -n f-log

%.o: %.cpp
	$(CC) $(FLAGS) -c -o $@ $<

-include $(SOURCES:.cpp=.d)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(FLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -f $(OBJECTS) $(SOURCES:.cpp=.d) main.out

