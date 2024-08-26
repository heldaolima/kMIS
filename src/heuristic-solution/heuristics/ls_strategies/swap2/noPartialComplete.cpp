#include "noPartialComplete.h"
#include "../../../data_structures/tabu.h"

bool LS_Swap2_NoPartial_Complete::swap(Input *input, Solution &solution,
                                       int iteration) {
  int newObjective = 0, idxFirstRemove = 0, idxSecondRemove = 0,
      firstRemove = 0, secondRemove = 0;

  bitset<numberOfBits> partialBits, minusOne, newSolution;

  for (idxFirstRemove = 0; idxFirstRemove < input->k; idxFirstRemove++) {
    firstRemove = solution.subsetsInSolution[idxFirstRemove];
    if (tabu.isTabu(firstRemove, iteration))
      continue;

    for (idxSecondRemove = idxFirstRemove; idxSecondRemove < input->k;
         idxSecondRemove++) {
      if (idxFirstRemove == idxSecondRemove)
        continue;

      secondRemove = solution.subsetsInSolution[idxSecondRemove];

      if (tabu.isTabu(secondRemove, iteration))
        continue;

      partialBits = solution.bitsWithoutSet(input, {firstRemove, secondRemove});
      for (int i = 0; i < input->quantityOfSubsets; i++) {
        if (solution.isSubsetInSolution[input->subsets[i].identifier])
          continue;

        minusOne = partialBits & input->subsets[i].bits;
        for (int j = 0; j < input->quantityOfSubsets; j++) {
          if (i != j) {
            if (solution.isSubsetInSolution[input->subsets[j].identifier])
              continue;

            newSolution = minusOne & input->subsets[j].bits;
            newObjective = newSolution.count();
            if (newObjective > solution.getObjective()) {
              solution.swap(idxFirstRemove, input->subsets[i].identifier);
              solution.swap(idxSecondRemove, input->subsets[j].identifier,
                            &newSolution, newObjective);

              return true;
            }
          }
        }
      }
    }
  }

  return false;
}
