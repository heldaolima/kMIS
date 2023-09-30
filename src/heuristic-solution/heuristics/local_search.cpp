#include "local_search.h"
#include "../globals.h"
#include "../dbg.h"

void localSearch(Input input, Solution &initialSolution) {
  Solution newSolution(input.getQuantityOfSubsets());

  vector<int> subsetsNotInSolution;

  for (int i = 0; i < input.getQuantityOfSubsets(); i++) {
    if (!initialSolution.isSubsetInSolution[i])
      subsetsNotInSolution.push_back(i);
  }

  for (const int toBeRemoved: initialSolution.subsetsInSolution) {

    for (const int notInSolution : subsetsNotInSolution) {
      newSolution.clean(input.getQuantityOfSubsets());
      
      for (const int inSolution: initialSolution.subsetsInSolution) {
        if (inSolution != toBeRemoved) {
          newSolution.setIntersection(input.getSubset(inSolution));

          newSolution.addSubset(inSolution);
        }
      }

      newSolution.bits = intersection(newSolution.bits, input.getSubset(notInSolution));
      newSolution.addSubset(notInSolution);
      
      // newSolution.print();
      
      if (newSolution.getObjective() > initialSolution.getObjective()) {
        initialSolution = newSolution;
        return;
      }
    }
  }
}
