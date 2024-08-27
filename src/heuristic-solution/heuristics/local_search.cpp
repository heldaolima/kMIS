#include "local_search.h"

bool LocalSearch::swap1(Solution &solution, int iteration) {
  return this->_swap1->swap(input, solution, iteration);
}

bool LocalSearch::swap2(Solution &solution, int iteration) {
  return this->_swap2->swap(input, solution, iteration);
}
