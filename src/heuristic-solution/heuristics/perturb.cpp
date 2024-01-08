#include "perturb.h"
#include "grasp/construction_arrays.h"
#include "grasp/costs.h"
#include "grasp/lrc.h"
#include "../dbg.h"
#include <iostream>
#include <algorithm>

vector<Subset> getAvaliableSets(Solution*, Input*, int*);
void removeRandomSets(Solution&, int);
int getSizeOfAvaliableSubsets(vector<Subset> subsets);

Solution perturbReactive(Solution solution, Input* input, double alpha) {
  const int maximumNumberOfSetsToBeRemoved = (input->k / 2) + 1;
  const int numberOfSetsToBeRemoved = randintInterval(1, maximumNumberOfSetsToBeRemoved);

  int sizeOfAvaliableSets = 0;
  vector<Subset> avaliableSets = getAvaliableSets(&solution, input, &sizeOfAvaliableSets);

  removeRandomSets(solution, numberOfSetsToBeRemoved);
  solution.updateIntersection(avaliableSets);

  Costs costs(avaliableSets);
  Lrc lrc(avaliableSets.size());
  
  int i = solution.subsetsInSolution.size();
  while (i < input->k) {
    int inferiorLimit = getInferiorLimit(alpha, costs.c_min, costs.c_max);
    int tam_lrc = lrc.set(solution, costs.incremental_cost, inferiorLimit); 

    int random_index = randint(tam_lrc);
    int chosenFromLRC = lrc.getIth(random_index); 

    solution.addSubsetAndUpdateIntersection(avaliableSets[chosenFromLRC]);

    if (i + 1 == input->k) {
      break;
    }

    costs.update(solution, avaliableSets);

    i++;
  }
  
  return solution;
}

vector<Subset> getAvaliableSets(Solution* solution, Input* input, int* numberOfSets) {
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

void removeRandomSets(Solution& solution, int numberOfSets) {
  for (int i = 0; i < numberOfSets; i++) {
    int idxRemove = randint(solution.subsetsInSolution.size());
    solution.removeSubset(idxRemove, solution.subsetsInSolution[idxRemove]);
  }
}
