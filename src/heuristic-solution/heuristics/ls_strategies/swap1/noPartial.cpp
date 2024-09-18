#include "noPartial.h"
#include "../../../data_structures/tabu.h"
#include "../../../globals.h"

bool LS_Swap1_NoPartial::swap(const Input *input, Solution &solution,
                              int iteration) {

  for (int idxRemove = 0; idxRemove < input->k; idxRemove++) {
    const int remove = solution.subsetsInSolution[idxRemove];
    if (tabu.isTabu(remove, iteration))
      continue;

    bitset<numberOfBits> partialBits = solution.bitsWithoutSet(input, {remove});
    for (int i = 0; i < input->subsets.size(); i++) {
      if (!solution.isSubsetInSolution[input->subsets[i].identifier] &&
          input->subsets[i].identifier != remove) {
        bitset<numberOfBits> newSolutionBits = partialBits & input->subsets[i].bits;
        int newObjective = newSolutionBits.count();

        if (newObjective > solution.getObjective()) {
          tabu.setTabu(input->subsets[i].identifier, iteration);
          solution.swap(idxRemove, input->subsets[i].identifier, newSolutionBits,
                        newObjective);
          return true;
        }
      }
    }
  }

  return false;
}
