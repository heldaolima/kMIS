#include "usePartial.h"
#include "../../../globals.h"
#include "../../../data_structures/partialSolution.h"
#include "../../../data_structures/tabu.h"

bool LS_Swap1_UsePartial::swap(Input* input, Solution &solution, int iteration) {
  partialSolutions.computeOne(&solution);

  bitset<numberOfBits> bits;
  bits.set();
  int i = 0, newObjective = 0, idxRemove = 0, remove;

  for (idxRemove = 0; idxRemove < input->k; idxRemove++) {
    remove = solution.subsetsInSolution[idxRemove];
    if (
      !partialSolutions.interesting(remove) || 
      tabu.isTabu(remove, iteration)
    ) continue;

    for (i = 0; i < input->quantityOfSubsets; i++) {
      if (tabu.isTabu(input->subsets[i].identifier, iteration)) 
        continue;

      if (
        input->subsets[i].identifier != remove &&
        !solution.isSubsetInSolution[i]
      ) {
        bits = intersection(partialSolutions.listOne[remove].bits,
                            input->subsets[i].bits);

        newObjective = bits.count();
        if (newObjective > solution.getObjective()) {
          tabu.setTabu(input->subsets[i].identifier, iteration);

          solution.swap(idxRemove, input->subsets[i].identifier, &bits, newObjective);
          return true;
        }
      }
    }
  }

  return false;
}

