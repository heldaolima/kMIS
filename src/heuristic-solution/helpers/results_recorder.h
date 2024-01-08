#ifndef results_recorder_h
#define results_recorder_h

#include <ctime>
#include <iostream>
#include <string>
#include <filesystem>
#include "../heuristic_factory.h"

namespace fs = std::filesystem;
using std::string;

#define NUMBER_OF_TESTS 10

typedef struct objectives {
  int current = 0, best = 0, worst = 0;
  double average = 0.0;
  double averageFound = 0.0;

  void set(int objective, int found, int iteration) {
    current = objective;
    average += objective;
    averageFound += found;

    if (iteration == 0) {
      best = current;
      worst = current;
    } 
    else {
      if (current > best) 
        best = current;
      if (current < worst)
        worst = current;
    }
  }

} Objectives;

typedef struct times {
  double current = 0.0, average = 0.0;

  void set(clock_t t1, clock_t t2) {
    current = (t2 - t1) / (double) CLOCKS_PER_SEC;
    average += current;
  }
} Times;

class Experiments {
private:
  string outPath;
  HeuristicFactory* factory;

  void writeResults(const string inputFileName, Objectives objs, Times times, int k);

public:
  Experiments(string outputPath, HeuristicFactory* factory) ;
  void testHeuristic(fs::directory_entry inputFile);
};

#endif
