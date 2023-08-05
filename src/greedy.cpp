#include "greedy.h"
#include <algorithm>


Solution greedySolution(vector<Element> mainSet) {
  Solution solution;
  vector<Element> sets = mainSet;

  std::sort(sets.begin(), sets.end(), Element::sortFunc);

  solution.addSubset(sets[0].id);

}