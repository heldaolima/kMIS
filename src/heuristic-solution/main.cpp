#include <iostream>
#include <string>
#include "dbg.h"
#include "random_utlis.h"
#include "data_structures/input.h"
#include "heuristics/greedy.h"
#include "heuristics/local_search.h"
#include "heuristics/grasp.h"
#include "heuristics/perturb.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: ./main.out <input_file>";
    return 1;
  }

  std::string path("../instances/");
  path.append(argv[1]);
  
  seed();
  Input input(path.c_str());
  // input.print();
  Solution solution = greedySolution(input);

  localSearch(input, solution);
  std::cout << "Greedy + Local Search: \n" ;
  solution.print();

  // Solution reactiveGraspSolution = reactiveGrasp(input);
  // std::cout << "GRASP (reativo): \n";
  // reactiveGraspSolution.print();

  log_info("Solution is going to perturb(): ");
  perturb(solution, input);

  // Solution pathRelinking = graspWithPathRelinking(input);
  // std::cout << "GRASP (reativo com path relinking): \n";
  // pathRelinking.print();
  
  return 0;
}
