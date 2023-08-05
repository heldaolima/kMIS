#ifndef KMIS_SOLUTION
#define KMIS_SOLUTION

#include <bitset>
#include <vector>
#include "globals.h"

using std::bitset, std::vector;

class Solution {
  public:
    bitset<nElems> bits;
    vector<bool> isInSolution;
    vector<int> elements;

    void clean();
    void setIsInSolution(int);
    void addSubset(int);
};

#endif