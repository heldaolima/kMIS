#include "local_search.h"
#include "../globals.h"
#include "../dbg.h"

void localSearch(Input input, Solution &initialSolution) {
  Solution newSolution(input.quantityOfSubsets);

  vector<int> subsetsNotInSolution;

  for (int i = 0; i < input.quantityOfSubsets; i++) {
    if (!initialSolution.isSubsetInSolution[i])
      subsetsNotInSolution.push_back(i);
  }

  for (const int toBeRemoved: initialSolution.subsetsInSolution) {

    for (const int notInSolution : subsetsNotInSolution) {
      newSolution.clean(input.quantityOfSubsets);
      
      for (const int inSolution: initialSolution.subsetsInSolution) {
        if (inSolution != toBeRemoved) {
          newSolution.bits = intersection(newSolution.bits, input.subsets[inSolution].bits);
          newSolution.addSubset(inSolution);
        }
      }

      newSolution.bits = intersection(newSolution.bits, input.subsets[notInSolution].bits);
      newSolution.addSubset(notInSolution);
      
      // newSolution.print();
      
      if (newSolution.bits.count() > initialSolution.bits.count()) {
        initialSolution = newSolution;
        return;
      }
    }

  }
}