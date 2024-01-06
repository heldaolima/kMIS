#ifndef __solution_h__
#define __solution_h__

#include "../globals.h"
#include "input.h"
#include <bitset>
#include <vector>

using std::vector;

class Solution {
private:
  unsigned int objective = 0;
public:
  bitset<numberOfBits> bits;
  vector<bool> isSubsetInSolution;
  vector<int> subsetsInSolution;

  Solution() {}
  Solution(int);
  void clean(int);
  void initializeIsSubsetInSolutionVec(int);
  void addSubsetAndUpdateIntersection(Subset);
  void addSubset(int);
  void removeSubset(int);
  void print();
  int getSubsetInSolution(int);
  int getObjective();
  int symmetricDifference(Solution);
  void updateIntersection(vector<Subset>);
  void updateBits(bitset<numberOfBits>);
  void updateBitsAndObjective(bitset<numberOfBits> bits);
  void setBitsAndObjective(bitset<numberOfBits> bits);
  void setBits(bitset<numberOfBits>);
  Solution copyWithoutSubset(Input* input, int subset);
  Solution copyWithoutSubsets(Input* input, int s1, int s2);
};

#endif
