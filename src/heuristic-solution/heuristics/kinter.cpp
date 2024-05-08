#include "kinter.h"
#include "../dbg.h"
#include "../globals.h"
#include <algorithm>
#include "../data_structures/partialSolution.h"

void GreedyKInter::setRestart(RestartSolution* restart) {
  this->restart = restart;
}

Solution GreedyKInter::run() {
  int i = 0;
  Solution solution(input->quantityOfSubsets);

  vector<Subset> subsets = input->subsets;
  std::sort(subsets.begin(), subsets.end(), input->sortByObjectiveFunc);

  solution.addSubset(subsets[0].identifier);
  solution.setBits(subsets[0].bits);
  bitset<numberOfBits> partialSolution = solution.bits;

  if (this->restart != nullptr) {
    restart->setSubsetAsUsed(subsets[0].identifier);
  }

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

  partialSolutions.computeOne(&solution);

  return solution;
}
