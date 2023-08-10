#include "greedy.h"
#include "../dbg.h"
#include "../globals.h"
#include <algorithm>

#define NDEBUG

Solution greedySolution(Entry entry) {
  Solution solution(entry.quantityOfSubsets);
  vector<Subset> subsets = entry.subsets;

  std::sort(subsets.begin(), subsets.end(), sortFunc);

  Subset biggestSet = subsets[0];
  solution.addSubset(biggestSet.identifier);
  bitset<numberOfBits> partialSolution = biggestSet.bits;

  int currentK = 1, i = 0;
  while (currentK < entry.k) {
    for (i = currentK; i < subsets.size(); i++) {
      subsets[i].bits = intersection(partialSolution, subsets[i].bits);
      subsets[i].qtd = subsets[i].bits.count();
    }
    std::sort(subsets.begin() + currentK, subsets.end(), sortFunc);
    Subset aux = subsets[currentK];
    partialSolution = aux.bits;
    solution.addSubset(aux.identifier);
    currentK++;
  }

  solution.bits = partialSolution;
  return solution;
}