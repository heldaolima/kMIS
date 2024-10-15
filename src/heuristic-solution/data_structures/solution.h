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

  double timeFound;

  Solution() {}
  Solution(int);
  void setTimeFound(clock_t t1, clock_t t2);
  void clean(int);
  void initializeIsSubsetInSolutionVec(int);
  void addSubsetAndUpdateIntersection(const Subset &subset);
  void addSubset(int);
  void removeSubset(int, int);
  void print();
  int getSubsetInSolution(int);
  int getObjective() const;
  int symmetricDifference(const Solution &sol);
  void updateIntersection(const vector<Subset> &sets);
  void updateBits(const bitset<numberOfBits> &);
  void updateBitsAndObjective(const bitset<numberOfBits> &bits);
  void setBitsAndObjective(const bitset<numberOfBits> &bits);
  void setBits(const bitset<numberOfBits> &);
  Solution copyWithoutSubsets(const Input &input, const RemoveSubsets &remove);
  bitset<numberOfBits> bitsWithoutSet(const Input *input,
                                      const RemoveSubsets &remove);
  void setIterationFoud(int it);
  unsigned int getIterationFound();
  void swap(int idxOut, int in);
  void swap(int idxOut, int in, const bitset<numberOfBits> &bits,
            int newObjective);
  void setObjective(unsigned int obj);
};

#endif
