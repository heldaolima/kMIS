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
  unsigned int iterationFound = 0;
  void swapSets(int idxOut, int in);
public:
  bitset<numberOfBits> bits;
  vector<bool> isSubsetInSolution;
  vector<int> subsetsInSolution;

  double timeFound = 0.0;

  Solution() {}
  Solution(int);
  void setTimeFound(clock_t t1, clock_t t2);
  void clean(int);
  void initializeIsSubsetInSolutionVec(int);
  void addSubsetAndUpdateIntersection(Subset);
  void addSubset(int);
  void removeSubset(int, int);
  void print();
  int getSubsetInSolution(int);
  int getObjective();
  int symmetricDifference(Solution);
  void updateIntersection(vector<Subset>);
  void updateBits(bitset<numberOfBits>);
  void updateBitsAndObjective(bitset<numberOfBits> bits);
  void setBitsAndObjective(bitset<numberOfBits> bits);
  void setBits(bitset<numberOfBits>);
  Solution copyWithoutSubsets(Input* input, RemoveSubsets remove);
  void setIterationFoud(int it);
  unsigned int getIterationFound();
  void swap(int idxOut, int in);
  void swap(int idxOut, int in, bitset<numberOfBits> *bits, int newObjective);
  void setObjective(unsigned int obj);
};

#endif
