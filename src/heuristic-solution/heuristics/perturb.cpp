#include "perturb.h"
#include "../data_structures/solutionMinusOne.h"
#include "../dbg.h"
#include "grasp/costs.h"
#include "grasp/lrc.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <unordered_set>

#define FLOOR 2

vector<Subset> getAvaliableSets(Solution *, Input *, int *);
void removeRandomSets(Solution &, int);
int getSizeOfAvaliableSubsets(vector<Subset> subsets);

Solution perturbReactive(Solution solution, Input *input, double alpha) {
  int i = 0;
  Solution perturbed = Solution(input->quantityOfSubsets);

  debug("solution in perturb: ");
  solution.print();

  int numberOfSetsToBeRemoved = std::ceil(std::sqrt(input->k));
  if (input->k + numberOfSetsToBeRemoved >= input->quantityOfSubsets) {
    numberOfSetsToBeRemoved = std::ceil(std::log(input->k));
  }

  debug("will remove %d elements", numberOfSetsToBeRemoved);

  int numberOfAvaliableSets = input->k;
  vector<int> avaliableSets = solution.subsetsInSolution;
  // newSubsetsInSolution;

  vector<bool> isAvaliable(input->quantityOfSubsets, true);

  for (int s : avaliableSets) {
    isAvaliable[s] = false;
  }

  for (i = 0; i < input->k - numberOfSetsToBeRemoved; i++) {
    int chosenIdx = randint(numberOfAvaliableSets);
    // newSubsetsInSolution.push_back(avaliableSets[chosenIdx]);

    perturbed.addSubset(avaliableSets[chosenIdx]);

    std::cout << "added " << avaliableSets[chosenIdx] << "\n";
    std::swap(avaliableSets[chosenIdx],
              avaliableSets[numberOfAvaliableSets - 1]);
    numberOfAvaliableSets--;
  }


  printVec(perturbed.subsetsInSolution);
  std::cout << "avaliable sets: ";
  printVec(avaliableSets);

  for (i = 0; i < numberOfAvaliableSets; i++) {
    minusOne.remove(avaliableSets[i]);
  }

  minusOne.print();

  // vector<Subset> avaliableSets = getAvaliableSets(&solution, input,
  // &sizeOfAvaliableSets);

  // removeRandomSets(solution, numberOfSetsToBeRemoved);
  // solution.updateIntersection(avaliableSets);

  // aqui: avaliableSets = todos os subconjuntos - os que foram usados
  Costs costs(&isAvaliable, &input->subsets);
  Lrc lrc(input->quantityOfSubsets);

  bitset<numberOfBits> intersec;
  intersec.set();

  for (int s : perturbed.subsetsInSolution) {
    intersec = intersection(intersec, input->subsets[s].bits);
    printf("intersec after adding %d: ", s);
    printBits(intersec);
  }

  //
  int inferiorLimit, tam_lrc, random_index, chosenFromLRC;
  i = perturbed.subsetsInSolution.size();
  while (i < input->k) {
    inferiorLimit = getInferiorLimit(alpha, costs.c_min, costs.c_max);
    tam_lrc = lrc.set(perturbed, costs.incremental_cost, inferiorLimit);
    // debug("tam_lrc: %d", tam_lrc);
    //
    random_index = randint(tam_lrc - 1);
    // randBetween(0, tam_lrc-1);
    // std::cout << "randomIndex: " << random_index << "\n";
    chosenFromLRC = lrc.getIth(random_index);
    // debug("chosen from lrc was %d", input->subsets[chosenFromLRC].identifier);
    // debug("from costs: %d", costs.incremental_cost[chosenFromLRC].identifier);

    isAvaliable[input->subsets[chosenFromLRC].identifier] = false;
    // debug("wil add %d", avaliableSets[chosenFromLRC].identifier);
    //
    intersec = intersection(intersec, input->subsets[chosenFromLRC].bits);
    printf("intersec after adding %d: ", input->subsets[chosenFromLRC].identifier);
    printBits(intersec);

    perturbed.addSubset(input->subsets[chosenFromLRC].identifier);
    //
    if (i + 1 == input->k) {
      break;
    }
    //
    costs.update(&isAvaliable, &input->subsets, &perturbed);
    i++;
  }
  //
  perturbed.setBitsAndObjective(intersec);
  perturbed.print();
  //
  minusOne.compute(&perturbed);
  //
  return perturbed;
}

vector<Subset> getAvaliableSets(Solution *solution, Input *input,
                                int *numberOfSets) {
  vector<Subset> avaliableSets;
  Subset dummy(-1);
  int qtd = 0;

  for (int i = 0; i < input->quantityOfSubsets; i++) {
    if (!solution->isSubsetInSolution[i]) {
      avaliableSets.push_back(input->subsets[i]);
      qtd++;
    } else {
      avaliableSets.push_back(dummy);
    }
  }

  *numberOfSets = qtd;
  return avaliableSets;
}

void removeRandomSets(Solution &solution, int numberOfSets) {
  for (int i = 0; i < numberOfSets; i++) {
    int idxRemove = randint(solution.subsetsInSolution.size());
    solution.removeSubset(idxRemove, solution.subsetsInSolution[idxRemove]);
    debug("will remove: %d", solution.subsetsInSolution[idxRemove]);
    // removeKey(solution.subsetsInSolution[idxRemove]);
  }
}
