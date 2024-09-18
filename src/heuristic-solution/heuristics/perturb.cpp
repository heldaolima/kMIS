#include "perturb.h"
#include "../data_structures/partialSolution.h"
#include "../dbg.h"
#include "grasp/costs.h"
#include "grasp/lrc.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>

Solution perturbReactive(const Solution &solution, const Input *input,
                         double alpha) {
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

  int chosenIdx;
  for (i = 0; i < input->k - numberOfSetsToBeRemoved; i++) {
    chosenIdx = randint(numberOfAvaliableSets);
    perturbed.addSubset(avaliableSets[chosenIdx]);

    std::swap(avaliableSets[chosenIdx],
              avaliableSets[numberOfAvaliableSets - 1]);

    numberOfAvaliableSets--;
  }

  Costs costs(isAvaliable, input->subsets);
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
    tam_lrc = lrc.set(perturbed, costs.incremental_cost, inferiorLimit);

    random_index = randBetween(0, tam_lrc - 1);
    chosenFromLRC = lrc.getIth(random_index);

    isAvaliable[input->subsets[chosenFromLRC].identifier] = false;
    intersec = intersection(intersec, input->subsets[chosenFromLRC].bits);

    perturbed.addSubset(input->subsets[chosenFromLRC].identifier);

    if (i + 1 == input->k) {
      break;
    }

    costs.update(isAvaliable, input->subsets, perturbed);
    i++;
  }

  perturbed.setBitsAndObjective(intersec);

  return perturbed;
}
