#include <iostream>
#include "dbg.h"
#include "data_structures/input.h"
#include "heuristics/greedy.h"
#include "heuristics/local_search.h"

int main(int argc, char* argv[]) {
  Input input("input/classe_1_40_40.txt");
  // for (const Subset subset: input.subsets) {
  //   debug("subset %d", subset.identifier);
  //   debug("%s", subset.bits.to_string().c_str());
  //   debug("%d\n", subset.bits.count());
  // }

  // std::cout << "\n\n";

  Solution solution = greedySolution(input);
  solution.print();

  localSearch(input, solution);
  solution.print();
  
  return 0;
}