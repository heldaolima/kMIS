#include "local_search.h"
#include "greedy.h"
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
          complete.print();
          std::cout << "\n\n";
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
      partialSolution.setBits(partialBits);
        // partialSolution.print();
      break;
    }

    for (int i = idx; i < subsets.size(); i++) { 
      subsets[i].setBits(intersection(partialBits, subsets[i].bits));
      // debug("subset %d got: %d | already in solution: %d", 
      //       subsets[i].identifier, subsets[i].qtd, partialSolution.isSubsetInSolution[subsets[i].identifier] ? 1 : 0);
    }

    std::sort(subsets.begin() + idx, subsets.end(), input.sortByObjectiveFunc);
  }

  // partialSolution.updateBitsAndObjective(partialBits);
}

// greedy swap(1, 1)
void greedyLocalSearchOne(Input input, Solution &solution) {
  Solution partialSolution; 
  GreedyKInter greedy(input);

  debug("original solution: ");
  solution.print();
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

