#ifndef results_recorder_h
#define results_recorder_h

#include <ctime>
#include <iostream>
#include <string>
#include <filesystem>
#include "../heuristic_factory.h"
#include "tester.h"
#include "results_writer.h"

namespace fs = std::filesystem;
using std::string;

class HeuristicTester: Tester {
private:
  ResultsWriter *writer;
  HeuristicsEnum type;

public:
  HeuristicTester(string outputPath, HeuristicsEnum type) ;
  void testFile(fs::directory_entry inputFile) override;
  ~HeuristicTester() {
    delete writer;
  }
};

#endif
