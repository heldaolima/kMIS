#include "vnd.h"
#include "local_search.h"
#include "../dbg.h"
#include "../data_structures/partialSolution.h"

void vnd(Input* input, Solution &solution, int iteration) {
  int it = 1;
  bool improvedOne = false, improvedTwo = false;
  Solution copy;
  LocalSearch ls = LocalSearch(input, iteration);
  while (it <= 2) {
    copy = solution;

    if (it == 1) {
      improvedOne = ls.swap1(copy);
      if (improvedOne) {
        partialSolutions.computeOne(&copy);
      } else {
        partialSolutions.computeTwo(&copy);
      }
    } else if (it == 2) {
      improvedTwo = ls.swap2Complete(copy);
      if (improvedTwo) {
        partialSolutions.computeOne(&copy);
      }
    }

    if (copy.getObjective() <= solution.getObjective()) {
      it++;
    } else {
      solution = copy;
      it = 1;
    }
  }
}
