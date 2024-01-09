#include "local_search.h"
#include "../globals.h"
#include "../dbg.h"
#include <iostream>
#include <algorithm>

// simple swap(1, 1)
void localSearch(Input* input, Solution &initialSolution) {
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
            return;
          }
      }
    }
  }
}

void greedyStep(int currentK, Input* input, Solution* partialSolution, RemoveSubsets remove) {
  vector<Subset> subsets;

  int idx = 0;
  for (const Subset subset : input->subsets) {
    if (remove.isDifferent(subset.identifier) && !partialSolution->isSubsetInSolution[subset.identifier]) {
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
}

// greedy swap(1, 1)
void greedyLocalSearchOne(Input* input, Solution &solution) {
  Solution partialSolution; 

  for (const int removeFromSolution : solution.subsetsInSolution) {
    partialSolution = solution.copyWithoutSubsets(input, { removeFromSolution });
    greedyStep(input->k - 1, input, &partialSolution, { removeFromSolution });
    
    if (partialSolution.getObjective() > solution.getObjective()) {
      solution = partialSolution;
      return;
    }
  }
}

// greedy swap(2,2)
void greedyLocalSearchTwo(Input* input, Solution &solution) {
  Solution partialSolution;

  for (int i = 0; i < input->k - 1; i++) {
    int s1 = solution.subsetsInSolution[i];
    int s2 = solution.subsetsInSolution[i+1];

    partialSolution = solution.copyWithoutSubsets(input, { s1, s2 });
    greedyStep(input->k - 2, input, &partialSolution, { s1, s2 });

    if (partialSolution.getObjective() > solution.getObjective()) {
      solution = partialSolution;
      return;
    }
  }
}
