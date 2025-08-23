#include "usePartial.h"
#include "../../../data_structures/partialSolution.h"
#include "../../../data_structures/tabu.h"
#include "../../../globals.h"
#include "../../../dbg.h"

bool LS_Swap1_UsePartial::swap(const Input *input, Solution &solution,
                               int iteration) {
  partialSolutions.computeOne(solution);

  bool improved = false;
  Solution newBest = solution;
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
        if (newObjective > newBest.getObjective()) { // compare it with the current improving solution
          tabu.setTabu(input->subsets[i].identifier, iteration);
          
          newBest.swap(idxRemove, input->subsets[i].identifier,
            newSolutionBits, newObjective);
          // debug("Got an improvement. Old solution was=%d, new solution is=%d", solution.getObjective(), newBest.getObjective());
          improved = true;
        }
      }
    }
  }

  if (improved) {
    solution = newBest;
    // debug("There was an improvement, so now current solution is %d", solution.getObjective());
  }

  return improved;
}
