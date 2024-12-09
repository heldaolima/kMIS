#include "extended_kinter.h"
#include "../../dbg.h"
#include "../../globals.h"
#include <algorithm>
#include <iostream>
#include <utility>

void ExtendedKInter::setTime(clock_t t1) { this->t1 = t1; }

Solution ExtendedKInter::run() {
  vector<Subset> originalSets = input->subsets, loopSets;
  std::sort(originalSets.begin(), originalSets.end(),
            input->sortByObjectiveFunc);

  bitset<numberOfBits> partialBits, bestBits;

  Solution solution(input->quantityOfSubsets);

  clock_t t2;
  int bestIntersection = 0;
  int currentSet = 0;
  while (bestIntersection < originalSets[currentSet].getNumberOfElements() &&
         currentSet < input->quantityOfSubsets) {
    vector<int> subsetsInSolution;
    loopSets = originalSets;

    // current subset needs to get into the solution first
    std::swap(loopSets[0], loopSets[currentSet]);

    subsetsInSolution.push_back(loopSets[0].identifier);
    partialBits = loopSets[0].bits;

    int currentK = 1;
    int currentCount = 0;
    while (currentK < input->k) {
      for (int i = currentK; i < input->quantityOfSubsets; i++) {
        loopSets[i].setBits(intersection(partialBits, loopSets[i].bits));
      }

      std::sort(loopSets.begin() + currentK, loopSets.end(),
                input->sortByObjectiveFunc);
      subsetsInSolution.push_back(loopSets[currentK].identifier);

      partialBits = loopSets[currentK].bits;
      currentCount = partialBits.count();


      currentK++;
      t2 = clock();
      if (currentCount < bestIntersection)
        break;
    }

    if (currentCount > bestIntersection) {
      t2 = clock();
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

  for (int s : solution.subsetsInSolution) {
    solution.isSubsetInSolution[s] = true;
  }

  solution.setTimeFound(t1, t2);

  return solution;
}
