#include "path_relinking.h"

Solution pathRelinking(Solution& current, Solution elite) {
  
}

int symmetricDifference(Solution a, Solution b) {
  int count = 0, k = 0;
  for (int subset: a.subsetsInSolution) {
    k++;
    if (b.isSubsetInSolution[subset]) {
      count++;
    }
  }

  return (k - count);
}