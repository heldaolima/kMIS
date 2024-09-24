#include "parse_arguments.h"
#include "helpers/heuristic_tester.h"
#include "heuristic_factory.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"
#include "heuristics/ls_strategies/factories/no_partial_ls_factory.h"
#include "heuristics/ls_strategies/factories/use_partial_ls_factory.h"
#include <cxxopts.hpp>
#include <iostream>

HeuristicTester parseArguments(int argc, char **argv) {
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
      "f,file", "Output file name (default: results_ils.csv)",
      cxxopts::value<std::string>()->default_value("results_ils.csv"))(
      "h,help", "Print usage");

  const auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help() << "\n";
    exit(0);
  }

  Swap2StrategyEnum swap2Strategy;
  const std::string swap2Arg = result["swap2"].as<std::string>();
  if (swap2Arg == "before-and-after") {
    swap2Strategy = SWAP2_BEFORE_AND_AFTER;
  } else if (swap2Arg == "complete") {
    swap2Strategy = SWAP2_COMPLETE;
  }

  const bool useDataStructures = result["data-structures"].as<bool>();
  LS_StrategyFactory *lsFactory;
  if (useDataStructures) {
    lsFactory = new UsePartialLSFactory(swap2Strategy);
  } else {
    lsFactory = new NoPartialLSFactory(swap2Strategy);
  }

  const std::string stopArg = result["stop"].as<std::string>();
  StopStrategyEnum stop;
  if (stopArg == "time") {
    stop = STOP_TIME;
  } else if (stopArg == "iterations") {
    stop = STOP_ITERATIONS;
  }

  const std::string outFileName = result["file"].as<std::string>();
  std::cout << "outFileName: " << outFileName << "\n";

  return HeuristicTester(outFileName, lsFactory, stop);
}
