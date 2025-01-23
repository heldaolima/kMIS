#ifndef __acceptance_criteria_strategy_h__
#define __acceptance_criteria_strategy_h__

#include "../../data_structures/solution.h"

class AcceptanceCriteriaStrategy {
public:
  virtual ~AcceptanceCriteriaStrategy();
  virtual void accept(Solution &current, Solution &best, Solution &globalBest,
                      int iteration, clock_t t1) = 0;
  virtual string toString() = 0;
  virtual void print() = 0;
};

#endif
