#include <iostream>
#include <string>

#include "heuristics/perturb.h"
#include "heuristics/greedy.h"
#include "heuristics/ils.h"
#include "random_utlis.h"
#include "dbg.h"

int main(int argc, char* argv[]) {
  seed();

  if (argc < 2) {
    std::cout << "Usage: ./ils.out <input_file>";
    return 1;
  }

  std::string path("../instances/");
  path.append(argv[1]);
  
  Input input(path.c_str());

  Solution sol = Ils(input).ils();
  sol.print();

}
