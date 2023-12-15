#ifndef results_recorder_h
#define results_recorder_h

#include <vector>
#include <ctime>
#include <iostream>
#include <string>
#include "../heuristic_factory.h"

using std::vector, std::string;

#define NUMBER_OF_TESTS 10

typedef struct objectives {
  int current = 0, best = 0, worst = 0;
  double average = 0.0;
  vector<int> eachOne;

  void set(int objective, int iteration) {
    current = objective;
    average += objective;
    eachOne.push_back(objective);

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
  vector<double> eachOne;

  void set(clock_t t1, clock_t t2) {
    current = (t2 - t1) / (double) CLOCKS_PER_SEC;
    average += current;
    eachOne.push_back(current);
  }

} Times;

class Experiments {
private:
  string inputPath;
  string outPath;
  HeuristicFactory* factory;

  void writeResults(string inputPath, Objectives objs, Times times, int k);
public:
  Experiments(string outputPath, HeuristicFactory* factory) ;
  void testHeuristic(string inputPath);
};

#endif
