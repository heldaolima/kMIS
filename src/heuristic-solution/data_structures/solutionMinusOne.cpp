#include "solutionMinusOne.h"
#include <iostream>
#include <utility>
#include "../dbg.h"

map<int, partial> solutionMinusOne;
map<std::pair<int, int>, partial> solutionMinusTwo;

void computeSolutionMinusOne(Input* input, Solution* solution) {
  std::cout << "\n";
  solution->print();
  auto copy = solutionMinusOne;

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

  for (i = input->k - 1; i >= 0; i--) {
    partialBits = intersection(suffixResult, prefix[i]);
    suffixResult = intersection(suffixResult,
                                input->subsets[solution->subsetsInSolution[i]].bits);
    solutionMinusOne[solution->subsetsInSolution[i]] = {
      partialBits,
      partialBits == solution->bits,
    };
  }


  map<int, partial>::iterator it;
  std::cout << "Solution minus one: \n";
  for (it = solutionMinusOne.begin(); it != solutionMinusOne.end(); it++) {
    printf("[%d] { ss: %i, os: %i }: ", 
           it->first, it->second.sameAsSolution, it->second.isOutsideTheSolution);
    for (i = 0; i < numberOfBits; i++) {
      if (it->second.bits[i]) {
        std::cout << i << " ";
      }
    }
    std::cout << "\n";
  }
}

void removeKey(int key) {
  debug("will erase key: %d", key);
  int x = solutionMinusOne.erase(key);
  debug("erased: %d", x);
}
