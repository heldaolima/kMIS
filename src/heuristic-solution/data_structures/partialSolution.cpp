#include "partialSolution.h"
#include "../dbg.h"
#include "../globals.h"
#include "solution.h"

PartialSolution partialSolutions;

void PartialSolution::computeOne(const Solution &solution) {
  int i = 0;

  bitset<numberOfBits> partialBits;
  partialBits.set();

  bitset<numberOfBits> prefix[input->k];
  bitset<numberOfBits> suffixResult = partialBits;

  prefix[0] = partialBits;
  for (i = 1; i < input->k; i++) {
    prefix[i] = intersection(
        input->subsets[solution.subsetsInSolution[i - 1]].bits, prefix[i - 1]);
  }

  for (i = input->k - 1; i >= 0; i--) {
    partialBits = intersection(suffixResult, prefix[i]);
    suffixResult = intersection(
        input->subsets[solution.subsetsInSolution[i]].bits, suffixResult);

    listOne[solution.subsetsInSolution[i]] = {
        true,
        partialBits,
        partialBits.count() > solution.getObjective(),
    };
  }
}

void PartialSolution::computeTwo(const Solution &solution) {
  int newK = input->k - 1;

  bitset<numberOfBits> partialBits;
  partialBits.set();

  int i = 0, j = 0;
  bitset<numberOfBits> prefix[newK], suffixResult;

  int auxIdx;
  int minusOneSubset[newK];

  for (i = 0; i < input->k; i++) {
    auxIdx = 0;
    suffixResult.set();

    for (j = 0; j < input->k; j++) {
      if (j != i) {
        minusOneSubset[auxIdx++] = solution.subsetsInSolution[j];
      }
    }

    prefix[0].set();
    for (j = 1; j < newK; j++) {
      prefix[j] = input->subsets[minusOneSubset[j - 1]].bits & prefix[j - 1];
    }

    for (j = newK - 1; j >= 0; j--) {
      partialBits = prefix[j] & suffixResult;
      suffixResult = suffixResult & input->subsets[minusOneSubset[j]].bits;

      listTwo[solution.subsetsInSolution[i]][minusOneSubset[j]] = {
          true,
          partialBits,
          partialBits.count() > solution.getObjective(),
      };
    }
  }
  // printTwo();
}

void PartialSolution::remove(int idx) { listOne[idx].set = false; }

void PartialSolution::remove(int i, int j) { listTwo[i][j].set = false; }

bool PartialSolution::interesting(int idx) {
  return listOne[idx].set && listOne[idx].hasMoreElements;
}

bool PartialSolution::interesting(int i, int j) {
  return listTwo[i][j].set && listTwo[i][j].hasMoreElements;
}

void PartialSolution::printOne() {
  int i = 0;
  for (i = 0; i < input->quantityOfSubsets; i++) {
    if (listOne[i].set) {
      printf("[%d] (%i): ", i, listOne[i].hasMoreElements);
      printBits(listOne[i].bits);
    }
  }
}

void PartialSolution::printTwo() {
  for (int i = 0; i < input->quantityOfSubsets; i++) {
    for (int j = 0; j < input->quantityOfSubsets; j++) {
      if (i != j && listTwo[i][j].set) {
        printf("[%d, %d] (%i): ", i, j, listTwo[i][j].hasMoreElements);
        printBits(listTwo[i][j].bits);
      }
    }
  }
}
