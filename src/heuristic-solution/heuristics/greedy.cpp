#include "greedy.h"
#include "../dbg.h"
#include "../globals.h"
#include <algorithm>

/*
  A cada iteração, incluir um subconjunto ainda não incluso na solução
  tal que a interseção de seus elementos com os da solução parcial
  seja máxima. Para tanto, inicia-se com o subconjunto que contenha o 
  maior número de elementos.
*/
Solution greedySolution(Input input) {
  Solution solution(input.quantityOfSubsets);
  vector<Subset> subsets = input.subsets;

  std::sort(subsets.begin(), subsets.end(), input.sortByOrderFunc);

  Subset biggestSet = subsets[0];
  solution.addSubset(biggestSet.identifier);
  bitset<numberOfBits> partialSolution = biggestSet.bits;

  int currentK = 1, i = 0;
  while (currentK < input.k) {
    for (i = currentK; i < subsets.size(); i++) {
      subsets[i].bits = intersection(partialSolution, subsets[i].bits);
      subsets[i].qtd = subsets[i].bits.count();
    }

    std::sort(subsets.begin() + currentK, subsets.end(), input.sortByOrderFunc);

    partialSolution = subsets[currentK].bits;
    solution.addSubset(subsets[currentK].identifier);

    currentK++;
  }

  solution.bits = partialSolution;
  return solution;
}
