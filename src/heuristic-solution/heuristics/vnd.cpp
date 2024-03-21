#include "vnd.h"
#include "local_search.h"

void vnd(Input* input, Solution &solution, int iteration) {
  int it = 1;
  Solution copy;
  LocalSearch ls = LocalSearch(input, iteration);
  while (it <= 2) {
    copy = solution;

    if (it == 1)
      ls.greedyLocalSearchOne(copy);
    else if (it == 2)
      ls.greedyLocalSearchTwo(copy);

    if (copy.getObjective() <= solution.getObjective()) {
      it++;
    } else {
      solution = copy;
      it = 1;
    }
  }
}
