#include "local_search.h"
#include "../globals.h"
#include "../dbg.h"
#include <algorithm>
#include <iostream>
#include "tabu.h"
#include "../helpers/random_utils.h"
#include "../partialExperiments.h"

// simple swap(1, 1)
void LocalSearch::localSearch(Solution &initialSolution) {
  Solution partialSolution;

  for (const int removeFromSolution: initialSolution.subsetsInSolution) {
    partialSolution = initialSolution.copyWithoutSubsets(input, { removeFromSolution }); // O(n)

    for (const Subset fromOutsideTheSolution: input->subsets) {
      Solution complete = partialSolution;
      if (fromOutsideTheSolution.identifier != removeFromSolution &&
        !partialSolution.isSubsetInSolution[fromOutsideTheSolution.identifier]) {
          complete.updateBitsAndObjective(fromOutsideTheSolution.bits);
          complete.addSubset(fromOutsideTheSolution.identifier);
          // complete.print();
          // std::cout << "\n\n";
          if (complete.getObjective() > initialSolution.getObjective()) { // first improvement
            initialSolution = complete;
            // tabu.setTabu(fromOutsideTheSolution.identifier, iteration);
            return;
          }
      }
    }
  }
}

vector<int> LocalSearch::greedyStep(int currentK, Solution* partialSolution, RemoveSubsets remove) {
  vector<Subset> subsets;
  vector<int> addedSets;

  int idx = 0;
  for (const Subset subset : input->subsets) {
    if (
      // !tabu.isTabu(subset.identifier, iteration) &&
      remove != subset.identifier && 
      !partialSolution->isSubsetInSolution[subset.identifier]
    ) {
      subsets.push_back(subset);
      subsets[idx].setBits(intersection(partialSolution->bits, subset.bits));
      idx++;
    }   
  }

  std::sort(subsets.begin(), subsets.end(), input->sortByObjectiveFunc);
  idx = 0;

  bitset<numberOfBits> partialBits;
  while (currentK < input->k) {
    partialBits = subsets[idx].bits;
    partialSolution->addSubset(subsets[idx].identifier);
    addedSets.push_back(subsets[idx].identifier);

    idx++; currentK++;
    if (currentK == input->k) {
      break;
    }

    for (int i = idx; i < subsets.size(); i++) { 
      subsets[i].setBits(intersection(partialBits, subsets[i].bits));
    }

    std::sort(subsets.begin() + idx, subsets.end(), input->sortByObjectiveFunc);
  }

  partialSolution->setBitsAndObjective(partialBits);

  return addedSets;
}

// greedy swap(1, 1)
void LocalSearch::greedyLocalSearchOne(Solution &solution) {
  Solution partialSolution; 
  vector<int> addedSets;

  for (const int removeFromSolution : solution.subsetsInSolution) {
    if (tabu.isTabu(removeFromSolution, iteration)) {
      continue;
    }
    partialSolution = solution.copyWithoutSubsets(input, { removeFromSolution });
    addedSets = greedyStep(input->k - 1, &partialSolution, { removeFromSolution });
    
    if (partialSolution.getObjective() > solution.getObjective()) {
      solution = partialSolution;
      if (useTabu) {
        for (int s: addedSets) {
          tabu.setTabu(s, iteration);
        }
      }

      return;
    }
  }
}

// greedy swap(2,2)
void LocalSearch::greedyLocalSearchTwo(Solution &solution) {
  Solution partialSolution;
  vector<int> addedSets;

  int s1, s2, i, j;
  RemoveSubsets remove;
  for (i = 0; i < input->k-1; i++) {
    s1 = solution.subsetsInSolution[i];
    if (tabu.isTabu(s1, iteration))
      continue;

    s2 = solution.subsetsInSolution[i+1];
    if (tabu.isTabu(s2, iteration))
      continue;

    remove = { s1, s2 };

    partialSolution = solution.copyWithoutSubsets(input, remove); // O(N)
    addedSets = greedyStep(input->k - 2, &partialSolution, remove);

    if (partialSolution.getObjective() > solution.getObjective()) {
      solution = partialSolution;
      if (useTabu) {
        for (int s: addedSets) {
          tabu.setTabu(s, iteration);
        }
      }

      return;
    }
  }
}

void LocalSearch::randomLocalSearchTwo(Solution &solution) {
  Solution partialSolution;
  vector<int> addedSets;

  int s1, s2, i, j;
  RemoveSubsets remove;
  // bool usedSets[input->quantityOfSubsets];
  // for (i = 0; i < input->quantityOfSubsets; i++)
  //   usedSets[i] = false;

  for (i = 0; i < input->k-1; i++) {
    s1 = randint(input->quantityOfSubsets);
    // std::cout << "rand s1 is " << s1 << "\n";
    if (tabu.isTabu(s1, iteration))
      continue;

    s2 = randint(input->quantityOfSubsets);
    // std::cout << "rand s2 is " << s2 << "\n";
    if (s1 == s2 || tabu.isTabu(s2, iteration))
      continue;

    remove = { s1, s2 };

    partialSolution = solution.copyWithoutSubsets(input, remove); // O(N)
    addedSets = greedyStep(input->k - 2, &partialSolution, remove);

    if (partialSolution.getObjective() > solution.getObjective()) {
      solution = partialSolution;
      if (useTabu) {
        for (int s: addedSets) {
          tabu.setTabu(s, iteration);
        }
      }

      return;
    }
  }
}
