#include <iostream>
#include <string>
#include "dbg.h"
#include "random_utlis.h"
#include "data_structures/input.h"
#include "heuristics/greedy.h"
#include "heuristics/local_search.h"
#include "heuristics/grasp.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: ./main.out <input_file>";
    return 1;
  }

  std::string path("../instances/");
  path.append(argv[1]);
  
  seed();
  Input input(path.c_str());
  // for (const Subset subset: input.subsets) {
  //   debug("subset %d", subset.identifier);
  //   debug("%s", subset.bits.to_string().c_str());
  //   debug("%d\n", subset.bits.count());
  // }

  // std::cout << "\n\n";

  Solution solution = greedySolution(input);
  // solution.print();

  localSearch(input, solution);
  std::cout << "Greedy + Local Search: " << "\n";
  solution.print();

  Solution graspSolution = grasp(input);
  std::cout << "GRASP: " << "\n";
  graspSolution.print();
  
  return 0;
}