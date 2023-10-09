#include "perturb.h"
#include "grasp/construction_arrays.h"
#include "grasp/costs.h"
#include "grasp/lrc.h"
#include "../dbg.h"
#include <iostream>
#include <algorithm>

vector<Subset> getAvaliableSets(Solution, Input);
void removeRandomSets(Solution&, int);

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

  perturbed.updateIntersection(input);

  perturbed.print();

  return perturbed;
}

Solution perturbReactive(Solution solution, Input input, double alpha) {
  log_info("alpha: %lf", alpha);
  const int maximumNumberOfSetsToBeRemoved = (input.k / 2) + 1;
  const int numberOfSetsToBeRemoved = randint(maximumNumberOfSetsToBeRemoved);

  Solution perturbed = solution;
  vector<Subset> avaliableSets = getAvaliableSets(perturbed, input);

  removeRandomSets(perturbed, numberOfSetsToBeRemoved);
  solution.updateIntersection(input);

  log_info("Solution after having sets removed: ");
  perturbed.print();

  Costs costs(avaliableSets);
  Lrc lrc(avaliableSets.size());
  
  while (perturbed.subsetsInSolution.size() < input.k) {
    int inferiorLimit = costs.getInferiorLimit(alpha);
    log_info("Inferior limit: %d", inferiorLimit);

    int tam_lrc = lrc.set(perturbed, costs, inferiorLimit); 
    log_info("Tam_lrc: %d", tam_lrc);

    int random_index = randint(tam_lrc);
    log_info("Random index from lrc: %d", random_index);
    int chosenFromLRC = lrc.getIth(random_index); 
    log_info("Chosen from lrc: %d" , chosenFromLRC);

    perturbed.addSubset(chosenFromLRC);
    perturbed.updateIntersection(input);

    costs.update(perturbed, avaliableSets);
  }
  
  log_info("getting out of perturb.");
  return perturbed;
}

vector<Subset> getAvaliableSets(Solution solution, Input input) {
  input.sortByOrder();
  vector<Subset> avaliableSets;

  for (int i = 0; i < input.quantityOfSubsets; i++) {
    if (!solution.isSubsetInSolution[i]) {
      avaliableSets.push_back(input.subsets[i]);
    }
  }

  return avaliableSets;
}

void removeRandomSets(Solution& solution, int numberOfSets) {
  for (int i = 0; i < numberOfSets; i++) {
    int idxRemove = randint(solution.subsetsInSolution.size());
    solution.removeSubset(solution.subsetsInSolution[idxRemove]);
  }
}
