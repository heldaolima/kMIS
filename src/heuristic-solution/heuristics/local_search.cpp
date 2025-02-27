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

string LocalSearch::toString() const {
  return "Swap1_" + _swap1->toString() + "_" + _swap2->toString();
}

/* VND */
// TODO: decouple swap1 and swap2, since swap2 is not used anymore
void LocalSearch::run(Solution& solution, int iteration, clock_t t1) const {
  int it = 1;
  clock_t t2 = clock();
  bool improved;

  Solution copy;

  while (it <= 2) {
    copy = solution;

    if (it == 1) {
      improved = swap1(copy, iteration);
      t2 = clock();
      if (improved) {
        copy.setTimeFound(t1, t2);
      }
    } else if (it == 2) {
      improved = swap2(copy, iteration);
      t2 = clock();
      if (improved) {
        copy.setTimeFound(t1, t2);
      }
    }

    if (copy.getObjective() <= solution.getObjective()) {
      it++;
    } else {
      solution = copy;
      solution.timeFound = copy.timeFound;
      it = 1;
    }
  }
}
