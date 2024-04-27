#ifndef __solution_minus_one_h__
#define __solution_minus_one_h__

#include <map>
#include "../globals.h"
#include "solution.h"

using std::map;

typedef struct partial {
  bitset<numberOfBits> bits;
  bool sameAsSolution;
  bool isOutsideTheSolution = false;
} partial;

extern map<int, partial> solutionMinusOne;
void computeSolutionMinusOne(Input* input, Solution* solution);
void removeKey(int key);

#endif
