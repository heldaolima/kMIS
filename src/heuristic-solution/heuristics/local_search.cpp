#include "local_search.h"
#include "../globals.h"
#include "../dbg.h"
#include <iostream>
#include <algorithm>

// simple swap(1, 1)
void localSearch(Input input, Solution &initialSolution) {
  Solution partialSolution;

  for (const int removeFromSolution: initialSolution.subsetsInSolution) {
    partialSolution = initialSolution.copyWithoutSubset(&input, removeFromSolution); // O(n)

    for (const Subset fromOutsideTheSolution: input.subsets) {
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

void greedyStep(int currentK, Input& input, Solution& partialSolution, int removed) {
  bitset<numberOfBits> partialBits = partialSolution.bits;
  vector<Subset> subsets;

  int idx = 0;
  for (const Subset subset : input.subsets) {
    if (subset.identifier != removed && !partialSolution.isSubsetInSolution[subset.identifier]) {
      subsets.push_back(subset);
      subsets[idx].setBits(intersection(partialBits, subset.bits));
      idx++;
    }
  }

  std::sort(subsets.begin(), subsets.end(), input.sortByObjectiveFunc);
  idx = 0;
  while (currentK < input.k) {
    partialBits = subsets[idx].bits;
    partialSolution.addSubset(subsets[idx].identifier);

    idx++; currentK++;
    if (currentK == input.k) {
      break;
    }

    for (int i = idx; i < subsets.size(); i++) { 
      subsets[i].setBits(intersection(partialBits, subsets[i].bits));
      // debug("subset %d got: %d | already in solution: %d", 
      //       subsets[i].identifier, subsets[i].qtd, partialSolution.isSubsetInSolution[subsets[i].identifier] ? 1 : 0);
    }

    std::sort(subsets.begin() + idx, subsets.end(), input.sortByObjectiveFunc);
  }

  partialSolution.setBitsAndObjective(partialBits);
}

// greedy swap(1, 1)
void greedyLocalSearchOne(Input input, Solution &solution) {
  Solution partialSolution; 

  for (const int removeFromSolution : solution.subsetsInSolution) {
    partialSolution = solution.copyWithoutSubset(&input, removeFromSolution);
    partialSolution.print();
    greedyStep(input.k - 1, input, partialSolution, removeFromSolution);
    partialSolution.print();
    
    if (partialSolution.getObjective() > solution.getObjective()) {
      solution = partialSolution;
      return;
    }
  }
}

void greedyStep2(int currentK, Input& input, Solution& partialSolution, int r1, int r2) {
  bitset<numberOfBits> partialBits = partialSolution.bits;
  vector<Subset> subsets;

  int idx = 0;
  for (const Subset subset : input.subsets) {
    if (subset.identifier != r1 && subset.identifier != r2 && !partialSolution.isSubsetInSolution[subset.identifier]) {
      subsets.push_back(subset);
      subsets[idx].setBits(intersection(partialBits, subset.bits));
      idx++;
    }
  }

  std::sort(subsets.begin(), subsets.end(), input.sortByObjectiveFunc);
  idx = 0;
  while (currentK < input.k) {
    partialBits = subsets[idx].bits;
    partialSolution.addSubset(subsets[idx].identifier);

    idx++; currentK++;
    if (currentK == input.k) {
      break;
    }

    for (int i = idx; i < subsets.size(); i++) { 
      subsets[i].setBits(intersection(partialBits, subsets[i].bits));
      // debug("subset %d got: %d | already in solution: %d", 
      //       subsets[i].identifier, subsets[i].qtd, partialSolution.isSubsetInSolution[subsets[i].identifier] ? 1 : 0);
    }

    std::sort(subsets.begin() + idx, subsets.end(), input.sortByObjectiveFunc);
  }

  partialSolution.setBitsAndObjective(partialBits);
}

void greedyLocalSearchTwo(Input input, Solution &solution) {
  Solution partialSolution;

  for (int i = 0; i < input.k - 1; i++) {
    int s1 = solution.subsetsInSolution[i];
    int s2 = solution.subsetsInSolution[i+1];

    partialSolution = solution.copyWithoutSubsets(&input, s1, s2);
    partialSolution.print();
    greedyStep2(input.k - 2, input, partialSolution, s1, s2);
    debug("After greedy step:");
    partialSolution.print();

    if (partialSolution.getObjective() > solution.getObjective()) {
      solution = partialSolution;
      return;
    }
  }
}
