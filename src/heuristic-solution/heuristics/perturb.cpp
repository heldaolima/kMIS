#include "perturb.h"
#include "grasp/construction_arrays.h"
#include "grasp/costs.h"
#include "grasp/lrc.h"
#include "../dbg.h"
#include <iostream>
#include <algorithm>

vector<Subset> getAvaliableSets(Solution, Input);
void removeRandomSets(Solution&, int);
int getSizeOfAvaliableSubsets(vector<Subset> subsets);
Subset getAvaliableSet(int idx);

Solution perturb(Solution solution, Input input) {
  // @todo: pick a method for deciding this number
  int numberOfSetsToBeRemoved = 4; 

  Solution perturbed = solution;
  vector<Subset> avaliableSets = getAvaliableSets(solution, input);
  removeRandomSets(perturbed, numberOfSetsToBeRemoved);

  while (perturbed.subsetsInSolution.size() < input.k) {
    int setToAdd = randint(avaliableSets.size());
    perturbed.addSubset(avaliableSets[setToAdd].identifier);

    avaliableSets.erase(avaliableSets.begin() + setToAdd);
  }

  perturbed.updateIntersection(avaliableSets);

  perturbed.print();

  return perturbed;
}

Solution perturbReactive(Solution solution, Input input, double alpha) {
  // log_info("alpha: %lf", alpha);
  const int maximumNumberOfSetsToBeRemoved = (input.k / 2) + 1;
  const int numberOfSetsToBeRemoved = randintInterval(1, maximumNumberOfSetsToBeRemoved);
  // log_info("will remove %d sets", numberOfSetsToBeRemoved);

  Solution perturbed = solution;
  vector<Subset> avaliableSets = getAvaliableSets(perturbed, input);
  int sizeOfAvaliableSets = getSizeOfAvaliableSubsets(avaliableSets);
  // log_info("sizeOfAvaliableSets: %d | avaliableSets.size(): %zu", sizeOfAvaliableSets, avaliableSets.size());

  removeRandomSets(perturbed, numberOfSetsToBeRemoved);
  solution.updateIntersection(avaliableSets);

  Costs costs(avaliableSets);
  Lrc lrc(avaliableSets.size());
  
  int i = perturbed.subsetsInSolution.size();
  // log_info("starting at: %d | k = %d", i, input.k);
  while (i < input.k) {
    // debug("i: %d", i);
    int inferiorLimit = getInferiorLimit(alpha, costs.c_min, costs.c_max);
    int tam_lrc = lrc.set(perturbed, costs.incremental_cost, inferiorLimit); 

    int random_index = randint(tam_lrc);
    int chosenFromLRC = lrc.getIth(random_index); 
    // log_info("Chosen from lrc: %d" , chosenFromLRC);
    // log_info("it's situation on availableSets: %d, objective: %d", avaliableSets[chosenFromLRC].identifier, avaliableSets[chosenFromLRC].getNumberOfElements());

    perturbed.addSubsetAndUpdateIntersection(avaliableSets[chosenFromLRC]);
    

    if (i + 1 == input.k) {
      // log_info("i+1 == input.k [i = %d]", i);
      break;
    }

    costs.update(perturbed, avaliableSets);

    i++;
  }
  
  // log_info("getting out of perturb.");
  return perturbed;
}

vector<Subset> getAvaliableSets(Solution solution, Input input) {
  input.sortByOrder();
  vector<Subset> avaliableSets;
  Subset dummy(-1);

  for (int i = 0; i < input.quantityOfSubsets; i++) {
    if (!solution.isSubsetInSolution[i]) {
      avaliableSets.push_back(input.subsets[i]);
    } else {
      avaliableSets.push_back(dummy);
    }
  }

  return avaliableSets;
}

int getSizeOfAvaliableSubsets(vector<Subset> subsets) {
  int size = 0;
  for (const Subset s: subsets) {
    if (s.identifier != -1)
      size++;
  }

  return size;
}

Subset getAvaliableSet(vector<Subset> subsets, int ith) {
  int idx = 0;
  for (int i = 0; i < subsets.size(); i++) {
    if (subsets[i].identifier != -1) {
      if (idx == ith)
        return subsets[i];

      idx++;
    }
  }

  return subsets[idx];
}

void removeRandomSets(Solution& solution, int numberOfSets) {
  for (int i = 0; i < numberOfSets; i++) {
    int idxRemove = randint(solution.subsetsInSolution.size());
    solution.removeSubset(solution.subsetsInSolution[idxRemove]);
  }
}
