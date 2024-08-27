#ifndef __ls_strategy_h__
#define __ls_strategy_h__

#include "../../data_structures/solution.h"

class LocalSearchStrategy {
public:
  virtual ~LocalSearchStrategy() {}
  virtual bool swap(Input *input, Solution &solution, int iteration) = 0;
};

#endif
