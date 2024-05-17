#include "vnd.h"
#include "local_search.h"
#include "../dbg.h"
#include "../data_structures/partialSolution.h"
#include <ctime>

void vnd(Input* input, Solution &solution, int iteration, clock_t t1) {
  int it = 1;
  bool improvedOne = false, improvedTwo = false;
  LocalSearch ls = LocalSearch(input, iteration);

  clock_t t2 = clock();

  Solution copy;
  while (it <= 2) {
    copy = solution;

    if (it == 1) {
      improvedOne = ls.swap1(copy);
      t2 = clock();
      if (improvedOne) {
        copy.setTimeFound(t1, t2);
        partialSolutions.computeOne(&copy);
      } else {
        partialSolutions.computeTwo(&copy);
      }
    } else if (it == 2) {
      improvedTwo = ls.swap2(copy);
      t2 = clock();
      if (improvedTwo) {
        copy.setTimeFound(t1, t2);
        partialSolutions.computeOne(&copy);
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
