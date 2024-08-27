#ifndef __local_search_h__
#define __local_search_h__

#include "../data_structures/input.h"
#include "../data_structures/solution.h"
#include "../heuristic.h"
#include "ls_strategies/ls_strategy.h"

class LocalSearch {
private:
  Input *input;
  LocalSearchStrategy *_swap1, *_swap2;

public:
  LocalSearch(Input *input, int iteration, LocalSearchStrategy *swap1,
              LocalSearchStrategy *swap2)
      : input(input) {
    this->_swap1 = swap1;
    this->_swap2 = swap2;
  }

  bool swap1(Solution &solution, int iteration);
  bool swap2(Solution &solution, int iteration);
};

#endif
