#include "local_search.h"
#include "../globals.h"
#include "../dbg.h"
#include <iostream>

void localSearch(Input input, Solution &initialSolution) {
  Solution partialSolution(input.quantityOfSubsets);

  for (const int removeFromSolution: initialSolution.subsetsInSolution) {
    for (const int remainsInSolution: initialSolution.subsetsInSolution) {
      if (removeFromSolution != remainsInSolution) {
        partialSolution.updateBits(input.subsets[remainsInSolution].bits);
        partialSolution.addSubset(remainsInSolution);
      }
    }

    for (const Subset fromOutsideTheSolution: input.subsets) {
      Solution complete = partialSolution;
      if (!partialSolution.isSubsetInSolution[fromOutsideTheSolution.identifier]) {
        complete.updateBits(fromOutsideTheSolution.bits);
        complete.addSubset(fromOutsideTheSolution.identifier);
        // complete.print();
        if (complete.getObjective() > initialSolution.getObjective()) {
          std::cout << "found a better one\n";
          initialSolution = complete;
          return;
        }
      }
    }
    partialSolution.clean(input.quantityOfSubsets);
  }
  std::cout << "did not found a better one\n";
}

