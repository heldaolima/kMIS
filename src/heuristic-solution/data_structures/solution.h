#ifndef __solution_h__
#define __solution_h__

#include "../globals.h"
#include "input.h"
#include <vector>

using std::vector;

class Solution {
public:
  bitset<numberOfBits> bits;
  vector<bool> isSubsetInSolution;
  vector<int> subsetsInSolution;

  Solution(int);
  void clean(int);
  void initializeIsSubsetInSolutionVec(int);
  void addSubset(int);
  void removeSubset(int);
  void print();
  int getSubsetInSolution(int);
  int getObjective();
  int symmetricDifference(Solution);
  void updateIntersection(Input);
  void updateBits(bitset<numberOfBits>);
};

#endif
