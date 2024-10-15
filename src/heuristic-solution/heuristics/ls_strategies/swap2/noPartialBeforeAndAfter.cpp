#include "noPartialBeforeAndAfter.h"
#include "../../../data_structures/tabu.h"
#include "../../../globals.h"

bool LS_Swap2_NoPartial_BeforeAndAfter::swap(const Input *input,
                                             Solution &solution,
                                             int iteration) {
  for (int idxFirstRemove = 0; idxFirstRemove < input->k; idxFirstRemove++) {
    const int firstRemove = solution.subsetsInSolution[idxFirstRemove];
    if (tabu.isTabu(firstRemove, iteration))
      continue;

    for (int idxSecondRemove = 0; idxSecondRemove < input->k;
         idxSecondRemove++) {

      if (idxFirstRemove == idxSecondRemove)
        continue;

      const int secondRemove = solution.subsetsInSolution[idxSecondRemove];

      if (tabu.isTabu(secondRemove, iteration))
        continue;

      bitset<numberOfBits> partialBits =
          solution.bitsWithoutSet(input, {firstRemove, secondRemove});

      if (partialBits.count() <= solution.getObjective()) {
        continue;
      }
      for (int i = 0; i < input->quantityOfSubsets; i++) {
        const int idxBefore = getIdxBefore(i, input->quantityOfSubsets);
        const int idxAfter = getIdxAfter(i, input->quantityOfSubsets);

        if (tabu.isTabu(input->subsets[idxBefore].identifier, iteration) ||
            tabu.isTabu(input->subsets[idxAfter].identifier, iteration))
          continue;

        if (!solution.isSubsetInSolution[idxBefore] &&
            !solution.isSubsetInSolution[idxAfter]) {
          bitset<numberOfBits> newSolutionBits =
              partialBits & input->subsets[idxBefore].bits;

          newSolutionBits &= input->subsets[idxAfter].bits;

          const int newObjective = newSolutionBits.count();
          if (newObjective > solution.getObjective()) {
            solution.swap(idxFirstRemove, idxBefore);
            solution.swap(idxSecondRemove, idxAfter, newSolutionBits,
                          newObjective);

            tabu.setTabu(input->subsets[idxBefore].identifier, iteration);
            tabu.setTabu(input->subsets[idxAfter].identifier, iteration);

            return true;
          }
        }
      }
    }
  }
  return false;
}
