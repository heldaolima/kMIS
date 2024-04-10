#include "perturb.h"
#include "grasp/costs.h"
#include "grasp/lrc.h"
#include "../dbg.h"
#include <cmath>

#define FLOOR 2

vector<Subset> getAvaliableSets(Solution*, Input*, int*);
void removeRandomSets(Solution&, int);
int getSizeOfAvaliableSubsets(vector<Subset> subsets);

Solution perturbReactive(Solution solution, Input* input, double alpha) {
  // debug("k=%d numberOfSubsets=%d", input->k, input->quantityOfSubsets);
  int numberOfSetsToBeRemoved = std::ceil(std::sqrt(input->k));
  if (input->k + numberOfSetsToBeRemoved >= input->quantityOfSubsets)
    numberOfSetsToBeRemoved = std::ceil(std::log(input->k));
  // int numberOfSetsToBeRemoved = randintInterval(FLOOR, ceil); 
  // if (numberOfSetsToBeRemoved == ceil + 1)
  //   --numberOfSetsToBeRemoved;
  // debug("ceil=%d numberOfSetsToBeRemoved=%d", ceil, numberOfSetsToBeRemoved);
  
  int sizeOfAvaliableSets = 0;
  vector<Subset> avaliableSets = getAvaliableSets(&solution, input, &sizeOfAvaliableSets);

  removeRandomSets(solution, numberOfSetsToBeRemoved);
  solution.updateIntersection(avaliableSets);

  Costs costs(avaliableSets);
  Lrc lrc(avaliableSets.size());
  
  bitset<numberOfBits> intersec = solution.bits;

  int inferiorLimit, tam_lrc, random_index, chosenFromLRC;
  int i = solution.subsetsInSolution.size();
  while (i < input->k) {
    inferiorLimit = getInferiorLimit(alpha, costs.c_min, costs.c_max);
    tam_lrc = lrc.set(solution, costs.incremental_cost, inferiorLimit); 

    // int random_index = randint(tam_lrc); // divisao por zero
    random_index = randBetween(0, tam_lrc-1);
    chosenFromLRC = lrc.getIth(random_index); 
    // debug("chosenFromLRC=%d", chosenFromLRC);

    intersec = intersection(intersec, avaliableSets[chosenFromLRC].bits);
    solution.addSubset(avaliableSets[chosenFromLRC].identifier);
    // solution.addSubset(avaliableSets[chosenFromLRC].identifier);

    if (i + 1 == input->k) {
      break;
    }

    costs.update(&solution, avaliableSets);

    i++;
  }
  
  solution.setBitsAndObjective(intersec);
  // solution.print();
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
