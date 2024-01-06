#ifndef __local_search_h__
#define __local_search_h__

#include "../heuristic.h"
#include "../data_structures/input.h"
#include "../data_structures/solution.h"

void localSearch(Input input, Solution &initialSolution);
void greedyLocalSearchOne(Input input, Solution &solution);
void greedyLocalSearchTwo(Input input, Solution &solution);

#endif
