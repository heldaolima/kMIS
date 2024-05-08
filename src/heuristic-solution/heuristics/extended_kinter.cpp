#include "extended_kinter.h"
#include <algorithm>
#include "../dbg.h"

Solution ExtendedKInter::run() {
  int bestIntersection = 0, currentSet = 0, currentK = 0, currentCount = 0;

  vector<Subset> originalSets = input->subsets, loopSets;
  std::sort(originalSets.begin(), originalSets.end(), input->sortByObjectiveFunc);
  bitset<numberOfBits> partialBits, bestBits;

  Solution solution(input->quantityOfSubsets);

  debug("\noriginalSet[0]: %d", originalSets[currentSet].identifier);
  while (
    bestIntersection < originalSets[currentSet].getNumberOfElements() && 
    currentSet < input->quantityOfSubsets
  ) {
    vector<int> subsetsInSolution(input->k);
    loopSets = originalSets;
    
    // current subset needs to get into the solution first
    std::swap(loopSets[0], loopSets[currentSet]);

    subsetsInSolution[0] = loopSets[currentSet].identifier;
    partialBits = loopSets[currentSet].bits;

    currentK = 1;
    while (currentK < input->k) {
      for (int i = currentK; i < input->quantityOfSubsets; i++) {
        loopSets[i].setBits(intersection(partialBits, loopSets[i].bits));
      }

      std::sort(loopSets.begin() + currentK, loopSets.end(), input->sortByObjectiveFunc);
      subsetsInSolution[currentK] = loopSets[currentK].identifier;

      partialBits = loopSets[currentK].bits;
      currentCount = partialBits.count();

      currentK++;
      if (currentCount < bestIntersection) break;
    }

    if (currentCount > bestIntersection) {
      bestIntersection = currentCount;
      solution.bits = partialBits;
      solution.setObjective(currentCount);
      solution.subsetsInSolution = subsetsInSolution;

      if (currentCount == input->quantityOfSubsets) {
        // cannot get better than that
        break;
      }
    }

    currentSet++;
  }
  
  for (int s: solution.subsetsInSolution) {
    solution.isSubsetInSolution[s] = true;
  }

  return solution;
}
