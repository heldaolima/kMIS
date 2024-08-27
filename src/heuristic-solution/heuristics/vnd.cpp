#include "vnd.h"
#include "local_search.h"
#include <ctime>

void vnd(LocalSearch *ls, Solution &solution, int iteration, clock_t t1) {
  int it = 1;
  clock_t t2 = clock();
  bool improved;

  Solution copy;

  while (it <= 2) {
    copy = solution;

    if (it == 1) {
      improved = ls->swap1(copy, iteration);
      t2 = clock();
      if (improved) {
        copy.setTimeFound(t1, t2);
      }
    } else if (it == 2) {
      improved = ls->swap2(copy, iteration);
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
