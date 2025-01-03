#ifndef __perturb_strategy_h__
#define __perturb_strategy_h__

#include "../../data_structures/solution.h"
#include "get_number_strategies/get_number_to_remove_strategy.h"

class Perturbation {
protected:
  GetNumberToRemoveStrategy *removalNumberStrategy;

public:
  explicit Perturbation(GetNumberToRemoveStrategy *getNumber)
      : removalNumberStrategy(getNumber) {}

  virtual ~Perturbation();
  virtual Solution perturb(const Solution &solution, const Input *input) = 0;
  virtual void update(int currentIteration, const Solution &currentSolution,
                      const Solution &bestSolution) = 0;
  virtual void print() = 0;
  virtual string toString() = 0;
};

#endif
