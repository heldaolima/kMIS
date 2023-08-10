#include <iostream>
#include "data_structures/entry.h"
#include "heuristics/greedy.h"
#include "dbg.h"

int main(int argc, char* argv[]) {
  Entry entry("classe_1_40_40.txt");
  // for (const Subset subset: entry.subsets) {
  //   debug("%d", subset.identifier);
  //   std::cout << subset.bits.to_string() << "\n";
  //   // debug("%s", subset.bits.to_string());
  //   debug("%d\n", subset.bits.count());
  // }

  // std::cout << "\n\n";

  Solution solution = greedySolution(entry);
  std::cout << "Elements in solution: ";
  for (const int el : solution.subsetsInSolution) {
    std::cout << el << " ";
  }
  std::cout << "\n";
  // Graph graph(argv[1]);

  return 0;
}