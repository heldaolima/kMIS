#include "usePartialComplete.h"
#include "../../../data_structures/partialSolution.h"
#include "../../../data_structures/tabu.h"

bool LS_Swap2_UsePartial_Complete::swap(const Input *input, Solution &solution,
                                        int iteration) {
  partialSolutions.computeTwo(solution);

  for (int idxFirstRemove = 0; idxFirstRemove < input->k; idxFirstRemove++) {
    const int firstRemove = solution.subsetsInSolution[idxFirstRemove];

    if (tabu.isTabu(firstRemove, iteration))
      continue;

    for (int idxSecondRemove = idxFirstRemove; idxSecondRemove < input->k;
         idxSecondRemove++) {
      if (idxFirstRemove == idxSecondRemove)
        continue;

      const int secondRemove = solution.subsetsInSolution[idxSecondRemove];
      if (tabu.isTabu(secondRemove, iteration))
        continue;

      if (!partialSolutions.interesting(firstRemove, secondRemove))
        continue;

      for (int i = 0; i < input->quantityOfSubsets; i++) {
        if (solution.isSubsetInSolution[input->subsets[i].identifier])
          continue;

        bitset<numberOfBits> partialBits =
            partialSolutions.listTwo[firstRemove][secondRemove].bits &
            input->subsets[i].bits;

        for (int j = 0; j < input->quantityOfSubsets; j++) {
          if (i != j) {
            if (solution.isSubsetInSolution[input->subsets[j].identifier])
              continue;

            bitset<numberOfBits> newSolutionBits =
                partialBits & input->subsets[j].bits;
            const int newObjective = newSolutionBits.count();

            if (newObjective > solution.getObjective()) {
              tabu.setTabu(input->subsets[i].identifier, iteration);
              tabu.setTabu(input->subsets[j].identifier, iteration);

              solution.swap(idxFirstRemove, input->subsets[i].identifier);
              solution.swap(idxSecondRemove, input->subsets[j].identifier,
                            newSolutionBits, newObjective);

              return true;
            }
          }
        }
      }
    }
  }

  return false;
}
