#include "local_search.h"
#include "../globals.h"
#include "../dbg.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "tabu.h"
#include "../helpers/random_utils.h"
#include "../partialExperiments.h"
#include "../data_structures/solutionMinusOne.h"

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
  for (Subset subset : input->subsets) {
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
void LocalSearch::swap1(Solution &solution) {
  Solution partialSolution; 
  vector<int> addedSets;

  bitset<numberOfBits> bits;
  bits.set();
  int i = 0, pulei = 0;

  debug("\n\nswap1 doido");
  for (const int remove: solution.subsetsInSolution) {
    if (!minusOne.interesting(remove)) {
      // solutionMinusOne[remove].sameAsSolution) {
      pulei++;
      continue;
    }

    if (
      !minusOne.interesting(remove) ||
      tabu.isTabu(remove, iteration)) {
      continue;
    } 

    debug("will try to remove %d", remove);
    for (i = 0; i < input->quantityOfSubsets; i++) {
      printf("i=%d\n", i);
      if (
        input->subsets[i].identifier != remove &&
        !solution.isSubsetInSolution[i]
      ) {
        debug("vou tentar inserir: %d", input->subsets[i].identifier);
        bits = intersection(minusOne.list[remove].bits,
                            input->subsets[i].bits);

        {
          debug("did intersection: ");
          printBits(bits);
        }

        if (bits.count() > solution.getObjective()) {
          tabu.setTabu(input->subsets[i].identifier, iteration);
          solution.swap(remove, input->subsets[i].identifier, &bits);
          debug("\ndid the swap: ");
          solution.print();
          minusOne.remove(remove);

          minusOne.compute(&solution);
          // removeKey(remove);
          // computeSolutionMinusOne(input, &solution);
          debug("Pulei %d de %d e ainda melhorei", pulei, input->k);
          return;
        }
      }
    }
  }

  debug("Pulei %d de %d", pulei, input->k);
}

// greedy swap(2,2)
void LocalSearch::greedyLocalSearchTwo(Solution &solution) {
  debug("\n\nwill use ls22");
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
      debug("on ls222 will remove %d %d", s1, s2);
      minusOne.remove(s1);
      minusOne.remove(s2);
      // removeKey(s1);
      // removeKey(s2);
      solution = partialSolution;
      for (int s: addedSets) {
        if (useTabu)
          tabu.setTabu(s, iteration);
      }

      minusOne.compute(&solution);

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

  for (i = 0; i < input->k * 2; i++) {
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
