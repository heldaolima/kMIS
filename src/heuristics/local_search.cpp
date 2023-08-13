#include "local_search.h"
#include "../globals.h"
#include "../dbg.h"

void localSearch(Entry entry, Solution &initialSolution) {
  Solution newSolution(entry.quantityOfSubsets);

  for (int subsetOfInitialSolution = 0; 
      subsetOfInitialSolution < initialSolution.subsetsInSolution.size();
      subsetOfInitialSolution++) 
  {
    int sLine = 0;
    
    for (int idx_subsets = 0; idx_subsets < entry.quantityOfSubsets; idx_subsets++) {
      if (!initialSolution.isSubsetInSolution[idx_subsets]) {
        sLine = idx_subsets; // will get into new solution

        newSolution.clean(entry.quantityOfSubsets);
        
        for (int innerSubsetInInitialSolution = 0;
            innerSubsetInInitialSolution < initialSolution.subsetsInSolution.size();
            innerSubsetInInitialSolution++) 
        {
          int subsetInSolution = initialSolution.getSubsetInSolution(innerSubsetInInitialSolution);
          if (subsetOfInitialSolution != innerSubsetInInitialSolution) {  // intersection without s
            newSolution.bits = intersection(
              newSolution.bits,
              entry.subsets[subsetInSolution].bits
            );

            newSolution.addSubset(initialSolution.subsetsInSolution[innerSubsetInInitialSolution]);
          }
        }

        newSolution.bits = intersection(newSolution.bits, entry.subsets[sLine].bits);
        debug("%s", newSolution.bits.to_string().c_str());
        
        newSolution.addSubset(sLine);

        if (newSolution.bits.count() > initialSolution.bits.count()) {
          initialSolution.bits = newSolution.bits;
          initialSolution.subsetsInSolution = newSolution.subsetsInSolution;
          initialSolution.isSubsetInSolution = newSolution.isSubsetInSolution;
          debug("switching");
          return;
        }
      }
    }
  } 
}
