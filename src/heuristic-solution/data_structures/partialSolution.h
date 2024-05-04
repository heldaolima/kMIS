#ifndef __partial_solution_h__
#define __partial_solution_h__

#include <map>
#include <vector>
#include "../globals.h"
#include "input.h"
#include "solution.h"

using std::map;

typedef struct partial {
  bool set = false;
  bitset<numberOfBits> bits;
  bool hasMoreElements = false;
} partial;

class PartialSolution {
private:
  Input* input;
public:
  vector<partial> listOne;
  vector<vector<partial>> listTwo;

  PartialSolution() {}
  PartialSolution(Input *input): input(input) {
    listOne = vector<partial>(input->quantityOfSubsets);
    listTwo = vector(input->quantityOfSubsets, 
                     vector<partial>(input->quantityOfSubsets));
  };

  void computeOne(Solution* solution);
  void computeTwo(Solution* solution);
  void remove(int idx);
  void remove(int i, int j);
  void printOne();
  void printTwo();
  bool interesting(int idx);
  bool interesting(int i, int j);
};

void computeMinusTwoBAD(Input* input, Solution* sol);
void computeMinusTwoBetter(Input* input, Solution* solution);

extern PartialSolution partialSolutions; 


// extern map<int, partial> solutionMinusOne;
// void computeSolutionMinusOne(Input* input, Solution* solution);
// void removeKey(int key);

#endif
