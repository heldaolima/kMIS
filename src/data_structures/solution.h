#ifndef __solution_h__
#define __solution_h__

#include "../globals.h"
#include <vector>

using std::vector;

class Solution {
public:
  bitset<numberOfBits> bits;
  vector<bool> isSubsetInSolution;
  vector<int> subsetsInSolution;

  Solution(int);
  void clean();
  void initializeIsSubsetInSolutionVec(int);
  void addSubset(int);

};

#endif