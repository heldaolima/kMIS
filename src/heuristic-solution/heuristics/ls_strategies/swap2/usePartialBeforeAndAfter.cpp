#include "usePartialBeforeAndAfter.h"
#include "../../../data_structures/partialSolution.h"
#include "../../../data_structures/tabu.h"
#include "../../../globals.h"

bool LS_Swap2_UsePartial_BeforeAndAfter::swap(Input *input, Solution &solution,
                                              int iteration) {
  partialSolutions.computeTwo(&solution);

  int newObjective = 0, idxFirstRemove = 0, idxSecondRemove = 0,
      firstRemove = 0, secondRemove = 0;

  bitset<numberOfBits> newSolution;

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

      if (!partialSolutions.interesting(firstRemove, secondRemove))
        continue;

      for (int i = 0; i < input->quantityOfSubsets; i++) {
        int idxBefore = getIdxBefore(i, input->quantityOfSubsets);
        int idxAfter = getIdxAfter(i, input->quantityOfSubsets);

        if (tabu.isTabu(input->subsets[idxBefore].identifier, iteration) ||
            tabu.isTabu(input->subsets[idxAfter].identifier, iteration))
          continue;

        if (!solution.isSubsetInSolution[i] &&
            !solution.isSubsetInSolution[idxBefore] &&
            !solution.isSubsetInSolution[idxAfter]) {

          newSolution =
              partialSolutions.listTwo[firstRemove][secondRemove].bits &
              input->subsets[idxBefore].bits;

          newSolution &= input->subsets[idxAfter].bits;

          newObjective = newSolution.count();
          if (newObjective > solution.getObjective()) {
            solution.swap(idxFirstRemove, idxBefore);
            solution.swap(idxSecondRemove, idxAfter, &newSolution,
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

int LS_Swap2_UsePartial_BeforeAndAfter::getIdxBefore(int i, int qtd) {
  return ((i - 1) + qtd) % qtd;
}

int LS_Swap2_UsePartial_BeforeAndAfter::getIdxAfter(int i, int qtd) {
  return ((i + 1) + qtd) % qtd;
}
