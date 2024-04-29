#ifndef __solution_minus_one_h__
#define __solution_minus_one_h__

#include <map>
// #include <vector>
#include "../globals.h"
#include "input.h"
#include "solution.h"

using std::map;

typedef struct partial {
  bool set = false;
  bitset<numberOfBits> bits;
  bool sameAsSolution;
  // bool isOutsideTheSolution = false;
  bool less = false;
} partial;

class SolutionMinusOne {
private:
   Input* input;
public:
  vector<partial> list;

  SolutionMinusOne() {}
  SolutionMinusOne(Input *input): input(input) {
    list = vector<partial>(input->quantityOfSubsets);
  };

  void compute(Solution* solution);
  void remove(int idx);
  void print();
  bool interesting(int idx);
};

extern SolutionMinusOne minusOne; 


// extern map<int, partial> solutionMinusOne;
// void computeSolutionMinusOne(Input* input, Solution* solution);
// void removeKey(int key);

#endif
