#ifndef __simple_perturb_h__
#define __simple_perturb_h__

#include "../../data_structures/solution.h"
#include "../../dbg.h"
#include "get_number_strategies/get_number_to_remove_strategy.h"
#include "perturbation.h"

class SimplePerturbation : public Perturbation {
private:
  int setInitialSubsetsAsUnavaliable(const Solution &solution,
                                     vector<Subset> &setsForInsertion,
                                     const Input *input) const;

public:
  SimplePerturbation(GetNumberToRemoveStrategy *getNumber)
      : Perturbation(getNumber) {}

  virtual Solution perturb(const Solution &solution,
                           const Input *input) override;
  virtual void update(int currentIteration, const Solution &currentSolution,
                      const Solution &bestSolution) override;

  virtual void print() override {
    std::cout << toString() << "\n";
    removalNumberStrategy->print();
  }

  virtual string toString() override {
    return "SimplePerturbation";
  }
};

#endif
