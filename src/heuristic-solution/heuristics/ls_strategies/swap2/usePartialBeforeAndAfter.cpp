#include "usePartialBeforeAndAfter.h"
#include "../../../data_structures/partialSolution.h"
#include "../../../data_structures/tabu.h"
#include "../../../globals.h"

bool LS_Swap2_UsePartial_BeforeAndAfter::swap(const Input *input,
                                              Solution &solution,
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
        const int idxBefore = getIdxBefore(i, input->quantityOfSubsets);
        const int idxAfter = getIdxAfter(i, input->quantityOfSubsets);

        if (tabu.isTabu(input->subsets[idxBefore].identifier, iteration) ||
            tabu.isTabu(input->subsets[idxAfter].identifier, iteration))
          continue;

        if (!solution.isSubsetInSolution[i] &&
            !solution.isSubsetInSolution[idxBefore] &&
            !solution.isSubsetInSolution[idxAfter]) {

          bitset<numberOfBits> newSolutionBits =
              partialSolutions.listTwo[firstRemove][secondRemove].bits &
              input->subsets[idxBefore].bits;

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

int LS_Swap2_UsePartial_BeforeAndAfter::getIdxBefore(int i, int qtd) {
  return ((i - 1) + qtd) % qtd;
}

int LS_Swap2_UsePartial_BeforeAndAfter::getIdxAfter(int i, int qtd) {
  return ((i + 1) + qtd) % qtd;
}
