#ifndef __ls_strategy_h__
#define __ls_strategy_h__

#include "../../data_structures/solution.h"

class LocalSearchStrategy {
public:
  virtual ~LocalSearchStrategy(); 
  virtual void print() const = 0;
  virtual bool swap(const Input *input, Solution &solution, int iteration) = 0;
};

#endif
