#include "noPartial.h"
#include "../../../globals.h"
#include "../../../data_structures/tabu.h"

bool LS_Swap1_NoPartial::swap(Input* input, Solution &solution, int iteration) {
  int i = 0, newObjective = 0, idxRemove = 0, remove;
  bitset<numberOfBits> partialBits, newSolution;

  for (idxRemove = 0; idxRemove < input->k; idxRemove++) {
    remove = solution.subsetsInSolution[idxRemove];
    if (tabu.isTabu(remove, iteration))
      continue;

    partialBits = solution.bitsWithoutSet(input, { remove } );
    for (int i = 0; i < input->subsets.size(); i++) {
      if (
        !solution.isSubsetInSolution[input->subsets[i].identifier] &&
        input->subsets[i].identifier != remove
      ) {
        newSolution = partialBits & input->subsets[i].bits;
        newObjective = newSolution.count();

        if (newObjective > solution.getObjective()) {
          tabu.setTabu(input->subsets[i].identifier, iteration);
          solution.swap(idxRemove, input->subsets[i].identifier, &newSolution, newObjective);
          return true;
        }
      }
    }
  }

  return false;
}
