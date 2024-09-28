#include "local_search.h"

bool LocalSearch::swap1(Solution &solution, int iteration) const {
  return this->_swap1->swap(input, solution, iteration);
}

bool LocalSearch::swap2(Solution &solution, int iteration) const {
  return this->_swap2->swap(input, solution, iteration);
}

void LocalSearch::print() const {
  std::cout << "Swap1: ";
  _swap1->print();
  std::cout << "Swap2: ";
  _swap2->print();
}
