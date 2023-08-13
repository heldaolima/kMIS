#include <iostream>
#include "data_structures/entry.h"
#include "heuristics/greedy.h"
#include "dbg.h"

int main(int argc, char* argv[]) {
  Entry entry("classe_1_40_40.txt");
  // for (const Subset subset: entry.subsets) {
  //   debug("subset %d", subset.identifier);
  //   debug("%s", subset.bits.to_string().c_str());
  //   debug("%d\n", subset.bits.count());
  // }

  // std::cout << "\n\n";

  Solution solution = greedySolution(entry);
  solution.print();
  return 0;
}