#include "local_search.h"
#include "../globals.h"
#include "../dbg.h"
#include <algorithm>
#include "tabu.h"
#include "../helpers/random_utils.h"
#include "../partialExperiments.h"
#include "../data_structures/partialSolution.h"

bool LocalSearch::swap1(Solution &solution) {
  // printf("on swap1, solution: ");
  // solution.print();
  bitset<numberOfBits> bits;
  bits.set();
  int i = 0, newObjective = 0, idxRemove = 0, remove;

  // std::cout << "\nswap1\n";
  for (idxRemove = 0; idxRemove < input->k; idxRemove++) {
    remove = solution.subsetsInSolution[idxRemove];
    if (!partialSolutions.interesting(remove) || tabu.isTabu(remove, iteration)) continue;

    for (i = 0; i < input->quantityOfSubsets; i++) {
      if (tabu.isTabu(input->subsets[i].identifier, iteration)) continue;

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

bool LocalSearch::swap2(Solution& solution) {
  int newObjective = 0, idxFirstRemove = 0, idxSecondRemove = 0,
    firstRemove = 0, secondRemove = 0;

  bitset<numberOfBits> bits, copy;
  bits.set();

  for (idxFirstRemove = 0; idxFirstRemove < input->k; idxFirstRemove++) {
    firstRemove = solution.subsetsInSolution[idxFirstRemove];
    if (tabu.isTabu(firstRemove, iteration)) continue;

    for (idxSecondRemove = idxFirstRemove; idxSecondRemove < input->k; idxSecondRemove++) {
      if (idxFirstRemove == idxSecondRemove) continue;

      secondRemove = solution.subsetsInSolution[idxSecondRemove];

      if (tabu.isTabu(secondRemove, iteration)) continue;
      if (!partialSolutions.interesting(firstRemove, secondRemove)) 
        continue;

      for (int i = 0; i < input->quantityOfSubsets; i++) {
        int idxBefore = ((i-1) + input->quantityOfSubsets) % input->quantityOfSubsets;
        int idxAfter = ((i+1) + input->quantityOfSubsets) % input->quantityOfSubsets;

        if (
          tabu.isTabu(input->subsets[idxBefore].identifier, iteration) ||
          tabu.isTabu(input->subsets[idxAfter].identifier, iteration)
        ) continue;

        if (!solution.isSubsetInSolution[i] &&
          !solution.isSubsetInSolution[idxBefore] &&
          !solution.isSubsetInSolution[idxAfter]
        ) {

          bits = partialSolutions.listTwo[firstRemove][secondRemove].bits & input->subsets[idxBefore].bits;
          bits &= input->subsets[idxAfter].bits;

          newObjective = bits.count();
          if (newObjective > solution.getObjective()) {
            solution.swap(idxFirstRemove, idxBefore);
            solution.swap(idxSecondRemove, idxAfter, &bits, newObjective);

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

bool LocalSearch::swap2Complete(Solution& solution) { 
  int newObjective = 0, idxFirstRemove = 0, idxSecondRemove = 0,
    firstRemove = 0, secondRemove = 0;

  bitset<numberOfBits> bits, copy;
  bits.set();

  for (idxFirstRemove = 0; idxFirstRemove < input->k; idxFirstRemove++) {
    firstRemove = solution.subsetsInSolution[idxFirstRemove];
    // if (tabu.isTabu(firstRemove, iteration)) continue;

    for (idxSecondRemove = idxFirstRemove; idxSecondRemove < input->k; idxSecondRemove++) {
      if (idxFirstRemove == idxSecondRemove) continue;

      secondRemove = solution.subsetsInSolution[idxSecondRemove];

      // if (tabu.isTabu(secondRemove, iteration)) continue;
      if (!partialSolutions.interesting(firstRemove, secondRemove)) 
        continue;

      for (int i = 0; i < input->quantityOfSubsets; i++) {
        if (solution.isSubsetInSolution[input->subsets[i].identifier]) continue;
        bits = partialSolutions.listTwo[firstRemove][secondRemove].bits & input->subsets[i].bits;

        for (int j = 0; j < input->quantityOfSubsets; j++) {
          if (i != j) {
            if (solution.isSubsetInSolution[input->subsets[j].identifier]) continue;

            bits &= input->subsets[j].bits;
            newObjective = bits.count();

            if (newObjective > solution.getObjective()) {
              solution.swap(idxFirstRemove, input->subsets[i].identifier);
              solution.swap(idxSecondRemove, input->subsets[j].identifier, &bits, newObjective);

              // tabu.setTabu(input->subsets[i].identifier, iteration);
              // tabu.setTabu(input->subsets[j].identifier, iteration);

              return true;
            }
          }
        }
      }
    }
  }

  return false;
}
