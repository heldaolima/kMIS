#include "restart.h"
#include "../helpers/random_utils.h"
#include "../data_structures/partialSolution.h"
#include "../dbg.h"
#include <algorithm>

void RestartSolution::setSubsetAsUsed(int subset) {
  std::swap(avaliableSets[subset], avaliableSets[numberOfAvailableSets-1]);
  numberOfAvailableSets--;
  if (numberOfAvailableSets <= 1) {
    numberOfAvailableSets = input->quantityOfSubsets;
  }
}

Solution RestartSolution::run(clock_t t1) {
  int i = 0;
  Solution solution(input->quantityOfSubsets);
  vector<Subset> subsets = input->subsets;

  unsigned int start = randint(numberOfAvailableSets);
  setSubsetAsUsed(start);

  solution.addSubsetAndUpdateIntersection(subsets[start]);
  bitset<numberOfBits> partialSolution = solution.bits;

  subsets[start].qtd = input->quantityOfElements + 1; // gambs
  std::sort(subsets.begin(), subsets.end(), input->sortByObjectiveFunc);

  int currentK = 1;
  while (currentK < input->k) {
    for (i = currentK; i < input->quantityOfSubsets; i++) {
      subsets[i].setBits(intersection(partialSolution, subsets[i].bits));
    }

    std::sort(subsets.begin() + currentK, subsets.end(), input->sortByObjectiveFunc);

    partialSolution = subsets[currentK].bits;
    solution.addSubset(subsets[currentK].identifier);

    currentK++;
  }

  solution.updateBitsAndObjective(partialSolution);

  solution.setTimeFound(t1, clock());

  partialSolutions.computeOne(&solution);

  return solution;
}
