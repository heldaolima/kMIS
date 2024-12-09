#ifndef __perturb_strategy_h__
#define __perturb_strategy_h__

#include "../../data_structures/solution.h"
#include "../../dbg.h"
#include "get_number_to_remove_strategy.h"

class Perturbation {
private:
  GetNumberToRemoveStrategy *numberToRemoveGetter;

  int setInitialSubsetsAsUnavaliable(const Solution &solution,
                                     vector<Subset> &setsForInsertion,
                                     const Input *input) const;

public:
  Perturbation(GetNumberToRemoveStrategy *getNumber)
      : numberToRemoveGetter(getNumber) {
    if (numberToRemoveGetter == nullptr) {
      debug("nullptr fudeu");
    }
    debug("%d", numberToRemoveGetter->getNumber(10));
  }

  Solution perturb(const Solution &solution, const Input *input) const;
  ~Perturbation() {
    delete numberToRemoveGetter;
  }

};

#endif
