#include "parse_arguments.h"
#include "helpers/heuristic_tester.h"
#include "heuristic_factory.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"
#include "heuristics/ls_strategies/factories/no_partial_ls_factory.h"
#include "heuristics/ls_strategies/factories/use_partial_ls_factory.h"
#include "heuristics/perturb_strategies/factories/perturbation_factory.h"
#include "heuristics/perturb_strategies/factories/reactive_perturbation_factory.h"
#include "heuristics/perturb_strategies/factories/simple_perturbation_factory.h"
#include "heuristics/perturb_strategies/get_number_strategies/get_number_to_remove_strategy.h"
#include <cxxopts.hpp>
#include <iostream>

HeuristicTester parseArguments(int argc, char **argv) {
  cxxopts::Options options("kMIS",
                           "ILS algorithm kMIS for solving the kMIS problem.");
  options.add_options()(
      "d,data-structures",
      "Use auxiliary data structures in the local search phase")(
      "s,stop", "Type of stop condition [time | iterations]",
      cxxopts::value<std::string>()->default_value("time"))(
      "swap2", "Type of swap(2,2) strategy [before-and-after | complete] ",
      cxxopts::value<std::string>()->default_value("before-and-after"))(
      "f,file", "Output file name",
      cxxopts::value<std::string>()->default_value("results_ils.csv"))(
      "h,help", "Print usage")(
      "p,perturbation", "Type of perturbation [simple | reactive]",
      cxxopts::value<std::string>()->default_value("simple"))(
      "n,number",
      "Type of strategy for removing subsets in perturbation phase [root | "
      "proportion]",
      cxxopts::value<std::string>()->default_value("root"));

  const cxxopts::ParseResult result = options.parse(argc, argv);
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
  } else {
    std::cout << "Unknown option for swap(2, 2) strategy: " << swap2Arg << "\n";
    exit(1);
  }

  LS_StrategyFactory *lsFactory;
  if (result.count("data-structures")) {
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
  } else {
    std::cout << "Unknown option for type stop condition: " << stopArg << "\n";
    exit(1);
  }

  const std::string numberArg = result["number"].as<std::string>();
  NumberToRemoveEstrategyEnum getNumber;
  if (numberArg == "root") {
    getNumber = ROOT_OF_K;
  } else if (numberArg == "proportion") {
    getNumber = RANDOM_PROPORTION;
  } else {
    std::cout << "Unknown option for type of number removal strategy: "
              << numberArg << "\n";
    exit(1);
  }

  const std::string perturbArg = result["perturbation"].as<std::string>();
  PerturbationFactory *perturbationFactory;
  if (perturbArg == "simple") {
    perturbationFactory = new SimplePerturbationFactory(getNumber);
  } else if (perturbArg == "reactive") {
    perturbationFactory = new ReactivePerturbationFactory(getNumber);
  } else {
    std::cout << "Unknown option for perturbation type: " << perturbArg << "\n";
    std::exit(1);
  }

  const std::string outFileName = result["file"].as<std::string>();
  return HeuristicTester(outFileName, lsFactory, stop, perturbationFactory);
}
