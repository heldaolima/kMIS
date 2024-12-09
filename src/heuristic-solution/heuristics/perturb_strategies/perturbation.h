#ifndef __perturb_strategy_h__
#define __perturb_strategy_h__

#include "../../data_structures/solution.h"
#include "get_number_to_remove_strategy.h"

class Perturbation {
private:
  const GetNumberToRemoveStrategy *numberToRemoveGetter;

  int setInitialSubsetsAsUnavaliable(const Solution &solution,
                                     vector<Subset> &setsForInsertion,
                                     const Input *input) const;

public:
  Perturbation(const GetNumberToRemoveStrategy *numberToRemoveGetter)
      : numberToRemoveGetter(numberToRemoveGetter) {}

  Solution perturb(const Solution &solution, const Input *input) const;
};

#endif
