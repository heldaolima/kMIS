#ifndef __grasp_h__
#define __grasp_h__

#include "../data_structures/input.h"
#include "../data_structures/solution.h"

#define GRASP_MAX_ITERATIONS 500
#define TAM_X 11

class Grasp {
  double X[TAM_X] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
  Solution grasp(Input);
};

#endif