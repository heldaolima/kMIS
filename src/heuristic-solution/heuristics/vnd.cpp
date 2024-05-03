#include "vnd.h"
#include "local_search.h"
#include "../partialExperiments.h"
#include <iostream>
#include "../dbg.h"

void vnd(Input* input, Solution &solution, int iteration) {
  int it = 1;
  Solution copy;
  LocalSearch ls = LocalSearch(input, iteration);
  while (it <= 2) {
    copy = solution;

    if (it == 1) {
      ls.swap1(copy);
    }
    else if (it == 2) {
      if (useLocalSearchRand)
        ls.randomLocalSearchTwo(copy);
      else {
        ls.swap2(copy);
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
