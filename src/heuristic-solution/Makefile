CC=g++
FLAGS=-g -lm -O0

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
						
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: main.out

main.out: $(OBJECTS)
	$(CC) $(FLAGS) -o $@ $^

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
