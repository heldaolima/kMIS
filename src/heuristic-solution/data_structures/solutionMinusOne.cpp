#include "solutionMinusOne.h"
#include <iostream>
#include "../globals.h"
#include "../dbg.h"
#include "solution.h"

SolutionMinusOne minusOne; 

void SolutionMinusOne::compute(Solution* solution) {
  std::cout << "\n";
  solution->print();

  bitset<numberOfBits> partialBits;
  partialBits.set();

  int i = 0, j = 0, in, out;
  bitset<numberOfBits> prefix[input->k];
  bitset<numberOfBits> suffixResult = partialBits;

  prefix[0] = partialBits;
  for (i = 1; i < input->k; i++) {
    prefix[i] = intersection(input->subsets[solution->subsetsInSolution[i-1]].bits,
                             prefix[i-1]);
  }

  int count = 0;
  for (i = input->k - 1; i >= 0; i--) {
    partialBits = intersection(suffixResult, prefix[i]);
    count = partialBits.count();

    // printf("[%d] Count: %zu", solution->subsetsInSolution[i],
    //        partialBits.count());
    suffixResult = intersection(input->subsets[solution->subsetsInSolution[i]].bits,
                               suffixResult);

    list[solution->subsetsInSolution[i]] = {
      true,
      partialBits,
      partialBits == solution->bits,
      count == 0 || count < solution->getObjective() 
    };
  }

  this->print();
}

void SolutionMinusOne::remove(int idx) {
  list[idx].set = false;
}

bool SolutionMinusOne::interesting(int idx) {
    return list[idx].set && !list[idx].sameAsSolution && !list[idx].less;
}

void SolutionMinusOne::print() {
  int i = 0;
  for (i = 0; i < input->quantityOfSubsets; i++) {
    if (list[i].set) {
      printf("[%d] { eq = %i, le = %i } Bits: ", i, list[i].sameAsSolution, list[i].less);
      for (int b = 0; b < numberOfBits; b++) {
        if (list[i].bits[b]) {
          std::cout << b << " ";
        }
      }
      std::cout << "\n";
    }
  }
}
