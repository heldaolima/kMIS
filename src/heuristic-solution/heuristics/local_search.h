#ifndef __local_search_h__
#define __local_search_h__

#include "../data_structures/input.h"
#include "../data_structures/solution.h"
#include "../heuristic.h"
#include "ls_strategies/ls_strategy.h"
#include <iostream>

class LocalSearch {
private:
  const Input *input;
  LocalSearchStrategy *_swap1, *_swap2;

public:
  LocalSearch(const Input *input, LocalSearchStrategy *swap1,
              LocalSearchStrategy *swap2)
      : input(input), _swap1(swap1), _swap2(swap2) {}
  ~LocalSearch() {
    delete _swap1;
    delete _swap2;
  }

  bool swap1(Solution &solution, int iteration) const;
  bool swap2(Solution &solution, int iteration) const;
  void print() const;
};
#endif
