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
  ResultsWriter *writer;

public:
  HeuristicTester(string outputPath);
  void testFile(fs::directory_entry inputFile) override;
  ~HeuristicTester() { delete writer; }
};

#endif
