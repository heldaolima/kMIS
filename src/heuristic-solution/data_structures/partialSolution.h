#ifndef __partial_solution_h__
#define __partial_solution_h__

#include "../globals.h"
#include "input.h"
#include "solution.h"
#include <vector>

typedef struct partial {
  bool set = false;
  bitset<numberOfBits> bits;
  bool hasMoreElements = false;
} partial;

class PartialSolution {
private:
  const Input *input;

public:
  vector<partial> listOne;
  vector<vector<partial>> listTwo;

  PartialSolution() {}
  PartialSolution(const Input *input) : input(input) {
    listOne = vector<partial>(input->quantityOfSubsets);
    listTwo = vector(input->quantityOfSubsets,
                     vector<partial>(input->quantityOfSubsets));
  };

  void computeOne(const Solution &solution);
  void computeTwo(const Solution &solution);
  void remove(int idx);
  void remove(int i, int j);
  void printOne();
  void printTwo();
  bool interesting(int idx);
  bool interesting(int i, int j);
};

extern PartialSolution partialSolutions;

#endif
