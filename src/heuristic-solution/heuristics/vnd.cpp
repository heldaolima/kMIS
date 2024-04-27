#include "vnd.h"
#include "local_search.h"
#include "../partialExperiments.h"
#include <iostream>
#include "../dbg.h"

void vnd(Input* input, Solution &solution, int iteration) {
  int it = 1;
  Solution copy;
  std::cout << "inside vnd\n";
  LocalSearch ls = LocalSearch(input, iteration);
  // std::cout << "will perform ls 2,2\n";
  // ls.greedyLocalSearchTwo(solution);
  while (it <= 2) {
    debug("it: %d", it);
    copy = solution;

    if (it == 1) {
      ls.swap1(copy);
    }
    else if (it == 2) {
      if (useLocalSearchRand)
        ls.randomLocalSearchTwo(copy);
      else {
        debug("wil get into localsearchtwo");
        ls.greedyLocalSearchTwo(copy);
      }
    }

    if (copy.getObjective() <= solution.getObjective()) {
      debug("did not improve solution");
      it++;
    } else {
      solution = copy;
      it = 1;
    }
  }
}
