#include "local_search.h"
#include "../globals.h"
#include "../dbg.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "tabu.h"
#include "../helpers/random_utils.h"
#include "../partialExperiments.h"
#include "../data_structures/partialSolution.h"

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
  // printf("on swap1, solution: ");
  // solution.print();
  bitset<numberOfBits> bits;
  bits.set();
  int i = 0, newObjective = 0, idxRemove = 0, remove;

  // std::cout << "\nswap1\n";
  for (idxRemove = 0; idxRemove < input->k; idxRemove++) {
    remove = solution.subsetsInSolution[idxRemove];
    // debug("remove=%d", remove);
    // if (tabu.isTabu(remove, iteration)) continue;
    if (!partialSolutions.interesting(remove)) continue;

    // std::cout << "will try to remove " << remove << "\n";
    for (i = 0; i < input->quantityOfSubsets; i++) {
      if (
        input->subsets[i].identifier != remove &&
        !solution.isSubsetInSolution[i]
      ) {
        // debug("will insert %d", input->subsets[i].identifier);
        bits = intersection(partialSolutions.listOne[remove].bits,
                            input->subsets[i].bits);

        newObjective = bits.count();
        if (newObjective > solution.getObjective()) {
          tabu.setTabu(input->subsets[i].identifier, iteration);


          solution.swap(idxRemove, input->subsets[i].identifier, &bits, newObjective);

          // std::cout << "took out " << remove << " , inserted" << input->subsets[i].identifier << "\n";
          // std::cout << "improved, solution: ";
          // solution.print();

          partialSolutions.remove(remove);
          partialSolutions.compute(&solution);
          return;
        }
      }
    }
  }
}

void LocalSearch::swap2(Solution& solution) {
  int newObjective = 0, idxFirstRemove = 0, idxSecondRemove = 0,
    firstRemove = 0, secondRemove = 0;

  bitset<numberOfBits> bits, copy;
  bits.set();

  // std::cout << "\nswap2\n";
  // solution.print();

  for (idxFirstRemove = 0; idxFirstRemove < input->k; idxFirstRemove++) {
    firstRemove = solution.subsetsInSolution[idxFirstRemove];

    for (idxSecondRemove = 0; idxSecondRemove < input->k; idxSecondRemove++) {
      if (idxFirstRemove == idxSecondRemove) continue;

      secondRemove = solution.subsetsInSolution[idxSecondRemove];
      if (!partialSolutions.interesting(firstRemove, secondRemove)) 
        continue;

      for (int i = 0; i < input->quantityOfSubsets; i++) {
        int idxBefore = ((i-1) + input->quantityOfSubsets) % input->quantityOfSubsets;
        int idxAfter = ((i+1) + input->quantityOfSubsets) % input->quantityOfSubsets;
        // printf("i=%d, before=%d, after=%d\n", i, idxBefore, idxAfter);

        if (!solution.isSubsetInSolution[i] &&
          !solution.isSubsetInSolution[idxBefore] &&
          !solution.isSubsetInSolution[idxAfter]
        ) {

          // printf("firstRemove=%d, secondRemove=%d\n", firstRemove, secondRemove);
          // bits = partialSolutions.listTwo[firstRemove][secondRemove].bits & input->subsets[i].bits;
          bits = partialSolutions.listTwo[firstRemove][secondRemove].bits & input->subsets[idxBefore].bits;
          bits &= input->subsets[idxAfter].bits;

          newObjective = bits.count();
          // printf("in: %d & %d | new objective: %d\n", idxBefore, idxAfter, newObjective);
          if (newObjective > solution.getObjective()) {
            solution.swap(idxFirstRemove, idxBefore);
            solution.swap(idxSecondRemove, idxAfter, &bits, newObjective);

            partialSolutions.compute(&solution);
            return;
          }
        }
      }
    }
  }
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
      // minusOne.remove(s1);
      // minusOne.remove(s2);
      // removeKey(s1);
      // removeKey(s2);
      solution = partialSolution;
      for (int s: addedSets) {
        if (useTabu)
          tabu.setTabu(s, iteration);
      }

      // minusOne.compute(&solution);

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
