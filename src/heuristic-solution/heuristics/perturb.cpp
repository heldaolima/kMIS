#include "perturb.h"
#include "../dbg.h"
#include <iostream>
#include <algorithm>

Solution perturb(Solution solution, Input input) {
  // @todo: pick a method for deciding this number
  int numberOfSetsToBeRemoved = 4; 

  vector<int> avaliableSets(input.getQuantityOfSubsets() - input.getK());

  int subsetIdx = 0;
  for (int i = 0; i < input.getQuantityOfSubsets(); i++) {
    if (!solution.isSubsetInSolution[i]) {
      avaliableSets[subsetIdx] = i;
      subsetIdx++;
    }
  }

  Solution perturbed = solution;

  vector<int> toBeRemoved(numberOfSetsToBeRemoved);
  
  for (int i = 0; i < numberOfSetsToBeRemoved; i++) {
    int idxRemove = randint(perturbed.subsetsInSolution.size());
    toBeRemoved[i] = perturbed.subsetsInSolution[idxRemove];

    perturbed.removeSubset(toBeRemoved[i]);
  }

  while (perturbed.subsetsInSolution.size() < input.getK()) {
    int setToAdd = randint(avaliableSets.size());
    perturbed.addSubset(avaliableSets[setToAdd]);

    avaliableSets.erase(avaliableSets.begin() + setToAdd);
  }

  perturbed.updateBits(input);

  perturbed.print();

  return perturbed;
}

