#ifndef __local_search_h__
#define __local_search_h__

#include "../heuristic.h"
#include "../data_structures/input.h"
#include "../data_structures/solution.h"

class LocalSearch {
private:
  Input* input;
  int iteration;

  vector<int> greedyStep(int currentK, Solution* partialSolution, RemoveSubsets remove);
public:
  LocalSearch(Input* input, int iteration) : input(input) {
    this->iteration = iteration;
  }
  bool swap1(Solution &solution);
  bool swap2(Solution &solution);
  bool swap2Complete(Solution &solution);
};

#endif
