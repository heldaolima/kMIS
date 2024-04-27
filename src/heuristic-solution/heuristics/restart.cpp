#include "restart.h"
#include "../helpers/random_utils.h"
#include "../data_structures/solutionMinusOne.h"
#include "../dbg.h"
#include <algorithm>

void RestartSolution::setSubsetAsUsed(int subset) {
  wasUsedToStartSolution[subset] = true;
}

bool RestartSolution::checkUsed(int s) {
  return wasUsedToStartSolution[s];
}

Solution RestartSolution::run() {
  int i = 0;
  Solution solution(input->quantityOfSubsets);
  vector<Subset> subsets = input->subsets;

  unsigned int start = randint(input->quantityOfSubsets);
  while (wasUsedToStartSolution[start]) {
    start = randint(input->quantityOfSubsets);
  }

  // debug("will start with %d, id:%d", start, subsets[start].identifier);
  
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

  computeSolutionMinusOne(input, &solution);

  return solution;
}
