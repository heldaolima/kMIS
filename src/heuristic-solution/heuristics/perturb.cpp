#include "perturb.h"
#include "../data_structures/partialSolution.h"
#include "../dbg.h"
#include "grasp/costs.h"
#include "grasp/lrc.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>

Solution perturbReactive(Solution solution, Input *input, double alpha) {
  // debug("solution: ");
  // solution.print();
  int i = 0;
  Solution perturbed = Solution(input->quantityOfSubsets);

  int numberOfSetsToBeRemoved = std::ceil(std::sqrt(input->k));
  if (input->k + numberOfSetsToBeRemoved > input->quantityOfSubsets) {
    numberOfSetsToBeRemoved = std::ceil(std::log(input->k));
  }

  int numberOfAvaliableSets = input->k;
  vector<int> avaliableSets = solution.subsetsInSolution;

  vector<bool> isAvaliable(input->quantityOfSubsets, true);

  for (int s : avaliableSets) {
    isAvaliable[s] = false;
  }
  // printVec(isAvaliable);

  int chosenIdx;
  for (i = 0; i < input->k - numberOfSetsToBeRemoved; i++) {
    chosenIdx = randint(numberOfAvaliableSets);
    perturbed.addSubset(avaliableSets[chosenIdx]);

    std::swap(avaliableSets[chosenIdx],
              avaliableSets[numberOfAvaliableSets - 1]);

    numberOfAvaliableSets--;
  }

  Costs costs(&isAvaliable, &input->subsets);
  Lrc lrc(input->quantityOfSubsets);

  bitset<numberOfBits> intersec;
  intersec.set();

  for (int s : perturbed.subsetsInSolution) {
    intersec = intersection(intersec, input->subsets[s].bits);
  }

  int inferiorLimit, tam_lrc, random_index, chosenFromLRC;
  i = perturbed.subsetsInSolution.size();
  while (i < input->k) {
    inferiorLimit = getInferiorLimit(alpha, costs.c_min, costs.c_max);
    // debug("inferior limit: %d", inferiorLimit);
    tam_lrc = lrc.set(&perturbed, &costs.incremental_cost, inferiorLimit);
    // debug("tam_lrc: %d", tam_lrc);

    random_index = randBetween(0, tam_lrc-1);
    // debug("random_index: %d", random_index);
    chosenFromLRC = lrc.getIth(random_index);

    // debug("chosen=%d", input->subsets[chosenFromLRC].identifier);
    // std::cout << "is avaliable " << isAvaliable[chosenFromLRC] << "\n";
    isAvaliable[input->subsets[chosenFromLRC].identifier] = false;
    intersec = intersection(intersec, input->subsets[chosenFromLRC].bits);

    perturbed.addSubset(input->subsets[chosenFromLRC].identifier);

    if (i + 1 == input->k) {
      break;
    }

    costs.update(&isAvaliable, &input->subsets, &perturbed);
    i++;
  }

  perturbed.setBitsAndObjective(intersec);

  // perturbed.print();
  // debug("on perturb, check if perturbed is repeated");
  for (int i = 0; i < input->k; i++) {
    for (int j = 0; j < input->k; j++) {
      if (i != j && perturbed.subsetsInSolution[i] == perturbed.subsetsInSolution[j]) {
        printf("repeated: %d\n", perturbed.subsetsInSolution[j]);
        exit(1);
      }
    }
  
  }

  partialSolutions.compute(&perturbed);
  return perturbed;
}
