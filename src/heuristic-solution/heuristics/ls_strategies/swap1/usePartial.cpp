#include "usePartial.h"
#include "../../../data_structures/partialSolution.h"
#include "../../../data_structures/tabu.h"
#include "../../../globals.h"

bool LS_Swap1_UsePartial::swap(const Input *input, Solution &solution,
                               int iteration) {
  partialSolutions.computeOne(solution);

  for (int idxRemove = 0; idxRemove < input->k; idxRemove++) {
    const int remove = solution.subsetsInSolution[idxRemove];
    if (!partialSolutions.interesting(remove) || tabu.isTabu(remove, iteration))
      continue;

    for (int i = 0; i < input->quantityOfSubsets; i++) {
      if (tabu.isTabu(input->subsets[i].identifier, iteration))
        continue;

      if (input->subsets[i].identifier != remove &&
          !solution.isSubsetInSolution[i]) {
        bitset<numberOfBits> newSolutionBits = intersection(
            partialSolutions.listOne[remove].bits, input->subsets[i].bits);

        int newObjective = newSolutionBits.count();
        if (newObjective > solution.getObjective()) {
          tabu.setTabu(input->subsets[i].identifier, iteration);

          solution.swap(idxRemove, input->subsets[i].identifier,
                        newSolutionBits, newObjective);
          return true;
        }
      }
    }
  }

  return false;
}
