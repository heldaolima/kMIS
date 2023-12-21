#include "greedy.h"
#include "../dbg.h"
#include "../globals.h"
#include <algorithm>
#include <iostream>

/*
  A cada iteração, incluir um subconjunto ainda não incluso na solução
  tal que a interseção de seus elementos com os da solução parcial
  seja máxima. Para tanto, inicia-se com o subconjunto que contenha o 
  maior número de elementos.
*/
Solution GreedyKInter::run() {
  int i = 0;
  Solution solution(input.quantityOfSubsets);

  vector<Subset> subsets = input.subsets;
  std::sort(subsets.begin(), subsets.end(), input.sortByObjectiveFunc);

  solution.addSubset(subsets[0].identifier);
  solution.setBits(subsets[0].bits);

  greedyStep(1, subsets, solution);

  return solution;
}

void GreedyKInter::greedyStep(int currentK, vector<Subset> subsets, Solution& solution) {
  bitset<numberOfBits> partialSolution = solution.bits;

  // std::sort(subsets.begin() + currentK, subsets.end(), input.sortByObjectiveFunc);
  while (currentK < input.k) {
    for (int i = currentK; i < subsets.size(); i++) { 
      subsets[i].setBits(intersection(partialSolution, subsets[i].bits));
    }

    std::sort(subsets.begin() + currentK, subsets.end(), input.sortByObjectiveFunc);

    partialSolution = subsets[currentK].bits;
    solution.addSubset(subsets[currentK].identifier);

    currentK++;
  }

  solution.bits = partialSolution;
}
