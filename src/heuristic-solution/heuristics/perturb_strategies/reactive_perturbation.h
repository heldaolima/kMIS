#ifndef __reactive_perturbation_h__
#define __reactive_perturbation_h__

#include "../grasp/construction_arrays.h"
#include "get_number_strategies/get_number_to_remove_strategy.h"
#include "perturbation.h"
#include <iostream>

class ReactivePerturbation : public Perturbation {
private:
  constructionArrays auxArrays;
  int idxAlpha;

public:
  ReactivePerturbation(GetNumberToRemoveStrategy *getNumber)
      : Perturbation(getNumber) {}

  virtual Solution perturb(const Solution &solution,
                           const Input *input) override;
  virtual void update(int currentIteration, const Solution &currentSolution,
                      const Solution &bestSolution) override;
  virtual void print() override {
    std::cout << "ReactivePertubation\n";
    removalNumberStrategy->print();
  }
};

#endif
