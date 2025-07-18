#ifndef results_recorder_h
#define results_recorder_h

#include "../heuristic_factory.h"
#include "../heuristics/perturb_strategies/factories/perturbation_factory.h"
#include "results_writer.h"
#include "tester.h"
#include <ctime>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;
using std::string;

class HeuristicTester : Tester {
private:
  const string header =
      "input,k,best,worst,avg_obj,avg_time_to_best,avg_time\n";
  const LS_StrategyFactory *lsFactory;
  const PerturbationFactory *perturbationFactory;
  const AcceptanceCriteriaFactory acceptanceFactory;
  HeuristicFactory heuristicFactory;
  const unsigned int numberOfTests = 10;
  const unsigned int numberOfTestsTTT = 100;
  ResultsWriter writer;
  bool ttt = false;
  bool partial = false;

public:
  HeuristicTester(const string &outputPath, const LS_StrategyFactory *lsFactory,
                  StopStrategyEnum stopStrategy, PerturbationFactory *pFactory,
                  AcceptanceCriteriaFactory acFactory)
      : lsFactory(lsFactory), perturbationFactory(pFactory),
        heuristicFactory(stopStrategy), acceptanceFactory(acFactory),
        writer(ResultsWriter(outputPath, header)) {}
  void testFile(const fs::directory_entry &inputFile) const override;
  void setTTT();
  bool isTTT();
  void setPartial();
  bool isPartial();
  void testTTT(const fs::directory_entry &inputFile, int target);
  void testPartial(const fs::directory_entry &inputFile);
  ~HeuristicTester() {
    delete lsFactory;
    delete perturbationFactory;
  }
};

#endif
