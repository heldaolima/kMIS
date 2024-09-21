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
#include "partialExperiments.h"

bool useTabu = false;

const string path = "../instances/";

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  seed();

  cxxopts::Options options("kMIS",
                           "ILS algorithm kMIS for solving the kMIS problem.");
  options.add_options()(
      "d,data-structures",
      "Use auxiliary data structures in the local search phase")(
      "s,stop", "Type of stop condition [time | iterations] (default: time)",
      cxxopts::value<std::string>()->default_value("time"))(
      "swap2",
      "Type of swap(2,2) strategy [before-and-after | complete] (default: "
      "before-and-after)",
      cxxopts::value<std::string>()->default_value("before-and-after"))(
      "h,help", "Print usage");

  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help() << "\n";
    exit(0);
  }

  Swap2StrategyEnum swap2Strategy;
  std::string swap2Arg = result["swap2"].as<std::string>();
  if (swap2Arg == "before-and-after") {
    swap2Strategy = SWAP2_BEFORE_AND_AFTER;
  } else if (swap2Arg == "complete") {
    swap2Strategy = SWAP2_COMPLETE;
  }

  bool useDataStructures = result["data-structures"].as<bool>();
  LS_StrategyFactory *lsFactory;
  if (useDataStructures) {
    lsFactory = new UsePartialLSFactory(swap2Strategy);
  } else {
    lsFactory = new NoPartialLSFactory(swap2Strategy);
  }

  std::string stopArg = result["stop"].as<std::string>();
  StopStrategyEnum stop;
  if (stopArg == "time") {
    stop = STOP_TIME;
  } else if (stopArg == "iterations") {
    stop = STOP_ITERATIONS;
  }

  string dirs[3] = {"type1", "type2", "type3"};

  HeuristicTester ilsExperiments("test_time.csv", lsFactory, stop);

  for (const string dir : dirs) {
    for (const auto &file : fs::directory_iterator(path + dir)) {
      if (file.exists()) {
        std::cout << file.path().filename() << "\n";
        ilsExperiments.testFile(file);
      }
    }
  }

  delete lsFactory;
  return 0;
}
