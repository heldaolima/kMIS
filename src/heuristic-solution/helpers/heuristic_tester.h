#ifndef results_recorder_h
#define results_recorder_h

#include "../heuristic_factory.h"
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
  const string header = "input,k,best,worst,avg_obj,avg_time_to_best\n";
  const LS_StrategyFactory *lsFactory;
  const StopStrategyEnum stopStrategy;
  const HeuristicFactory heuristicFactory;
  ResultsWriter *writer;

public:
  HeuristicTester(const string &outputPath, const LS_StrategyFactory *lsFactory,
                  StopStrategyEnum stopStrategy)
      : lsFactory(lsFactory), stopStrategy(stopStrategy),
        heuristicFactory(stopStrategy) {
    this->writer = new ResultsWriter(outputPath, header);
  }
  void testFile(const fs::directory_entry &inputFile) override;
  ~HeuristicTester() {
    delete writer;
    delete lsFactory;
  }
};

#endif
