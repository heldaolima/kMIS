#include <iostream>
#include <string>

#include "heuristics/perturb.h"
#include "heuristics/greedy.h"
#include "heuristics/ils.h"
#include "random_utlis.h"
#include "dbg.h"

#include "heuristics/grasp/construction_arrays.h"
#include "heuristics/grasp/construction.h"
#include "heuristics/perturb.h"

int main(int argc, char* argv[]) {
  seed();

  if (argc < 2) {
    std::cout << "Usage: ./ils.out <input_file>";
    return 1;
  }

  std::string path("../instances/");
  path.append(argv[1]);
  
  Input input(path.c_str());
  // for (const Subset s: input.subsets) {
  //   std::cout << s.identifier << " ";
  // }
  // std::cout << "\n";

  // constructionArrays auxArrays;
  // int idxAlpha = auxArrays.getIdxAlpha();
  // double alpha = X[idxAlpha];
  //
  // log_info("idxAlpha: %d | alpha: %lf", idxAlpha, alpha);
  //
  // Solution bestSolution = grasp_construction(input, alpha);
  // bestSolution.print();
  //
  // Solution perturbed = perturbReactive(bestSolution, input, alpha);
  // perturbed.print();
  Solution sol = Ils(input).ils();
  sol.print();

}
