#ifndef __perturb_strategy_h__
#define __perturb_strategy_h__

#include "../../data_structures/solution.h"
#include "get_number_to_remove_strategy.h"

class Perturbation {
private:
  const Input *input;
  const GetNumberToRemoveStrategy *numberToRemoveGetter;

  int setInitialSubsetsAsUnavaliable(const Solution &solution,
                                     vector<Subset> &setsForInsertion) const;
  public:
    Perturbation(const Input *input,
                 const GetNumberToRemoveStrategy *numberToRemoveGetter)
        : input(input), numberToRemoveGetter(numberToRemoveGetter) {}

    Solution perturb(const Solution &solution) const;
  };

#endif
