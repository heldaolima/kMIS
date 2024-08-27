#include "extended_kinter.h"
#include "../../data_structures/partialSolution.h"
#include "../../dbg.h"
#include "../../globals.h"
#include <algorithm>

void ExtendedKInter::setTime(clock_t t1) { this->t1 = t1; }

Solution ExtendedKInter::run() {
  int bestIntersection = 0, currentSet = 0, currentK = 0, currentCount = 0;

  vector<Subset> originalSets = input->subsets, loopSets;
  std::sort(originalSets.begin(), originalSets.end(),
            input->sortByObjectiveFunc);
  bitset<numberOfBits> partialBits, bestBits;

  Solution solution(input->quantityOfSubsets);

  clock_t t2;
  while (bestIntersection < originalSets[currentSet].getNumberOfElements() &&
         currentSet < input->quantityOfSubsets) {
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

      std::sort(loopSets.begin() + currentK, loopSets.end(),
                input->sortByObjectiveFunc);
      subsetsInSolution[currentK] = loopSets[currentK].identifier;

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

  partialSolutions.computeOne(&solution);

  return solution;
}
