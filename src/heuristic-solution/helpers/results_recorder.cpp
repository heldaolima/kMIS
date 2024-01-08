#include "results_recorder.h"
#include <fstream>

const string header = "input,k,avg_time,avg_objective,avg_it_best,worst,best\n";

Experiments::Experiments(string outPath, HeuristicFactory* factory) {
  this->outPath = outPath;
  this->factory = factory;

  std::ofstream outFile(outPath, std::ofstream::out);
  outFile << header;
  outFile.close();
}

void Experiments::testHeuristic(fs::directory_entry inputFile) {
  Objectives objs;
  Times times;
  clock_t t1, t2;
  
  Input input(inputFile.path());
  Heuristic* heuristic = factory->create(input);

  for (int i = 0; i < NUMBER_OF_TESTS; i++) {
    t1 = clock();
      Solution solution = heuristic->run();
    t2 = clock();

    times.set(t1, t2);
    objs.set(solution.getObjective(), solution.getIterationFound(), i);
  }

  delete heuristic;

  times.average /= NUMBER_OF_TESTS;
  objs.average /= NUMBER_OF_TESTS;
  objs.averageFound /= NUMBER_OF_TESTS;

  writeResults(inputFile.path().filename(), objs, times, input.k);
}

void Experiments::writeResults(const string inputFileName, Objectives objs, Times times, int k) {
  std::ofstream outFile(outPath, std::ios_base::app);

  outFile << inputFileName << ",";
  outFile << k << ",";
  outFile << times.average << "," << objs.average << ",";
  outFile << objs.averageFound << ",";
  outFile << objs.worst << "," << objs.best << "\n";

  outFile.close();
}
