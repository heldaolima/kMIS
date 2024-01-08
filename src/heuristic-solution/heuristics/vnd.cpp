#include "vnd.h"
#include "local_search.h"

void vnd(Input input, Solution &solution) {
  int it = 1;
  Solution copy;
  while (it <= 2) {
    copy = solution;

    if (it == 1)
      greedyLocalSearchOne(input, copy);
    else if (it == 2)
      greedyLocalSearchTwo(input, copy);

    if (copy.getObjective() <= solution.getObjective()) {
      it++;
    } else {
      solution = copy;
      it = 1;
    }
  }
}
