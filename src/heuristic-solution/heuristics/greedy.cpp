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
  Solution solution(input.getQuantityOfSubsets());
  vector<Subset> subsets = input.getSubsets();

  std::sort(subsets.begin(), subsets.end(), input.sortByOrderFunc);

  Subset biggestSet = subsets[0];
  solution.addSubset(biggestSet.getId());
  bitset<numberOfBits> partialSolution = biggestSet.getBits();

  int currentK = 1, i = 0;
  while (currentK < input.getK()) {
    for (i = currentK; i < subsets.size(); i++) {
      subsets[i].calculateAndSetIntersection(partialSolution);
    }

    std::sort(subsets.begin() + currentK, subsets.end(), input.sortByOrderFunc);

    partialSolution = subsets[currentK].getBits();
    solution.addSubset(subsets[currentK].getId());

    currentK++;
  }

  solution.bits = partialSolution;
  return solution;
}
