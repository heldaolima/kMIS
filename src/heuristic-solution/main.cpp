#include <ctime>
#include <cxxopts.hpp>
#include <filesystem>
#include <iostream>

#include "data_structures/input.h"
#include "helpers/heuristic_tester.h"
#include "helpers/random_utils.h"
#include "heuristic_factory.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"
#include "heuristics/ls_strategies/factories/no_partial_ls_factory.h"
#include "heuristics/ls_strategies/factories/use_partial_ls_factory.h"
#include "parse_arguments.h"
#include "partialExperiments.h"

bool useTabu = false;

const string path = "../instances/";

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  seed();

  HeuristicTester ilsExperiments = parseArguments(argc, argv);

  string dirs[3] = {"type1", "type2", "type3"};
  for (const string dir : dirs) {
    for (const auto &file : fs::directory_iterator(path + dir)) {
      if (file.exists()) {
        std::cout << file.path().filename() << "\n";
        ilsExperiments.testFile(file);
      }
    }
  }

  return 0;
}
