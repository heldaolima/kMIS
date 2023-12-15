#include "results_recorder.h"
#include <fstream>

const string header = "input\tk\tavg_time\tavg_objective\tworst\tbest\n";

Experiments::Experiments(string outPath, HeuristicFactory* factory) {
  this->outPath = outPath;
  this->factory = factory;

  std::ofstream outFile(outPath, std::ofstream::out);
  outFile << header;
  outFile.close();
}

void Experiments::testHeuristic(string inputPath) {
  Objectives objs;
  Times times;
  clock_t t1, t2;
  
  Input input(inputPath);
  Heuristic* heuristic = factory->create(input);

  for (int i = 0; i < NUMBER_OF_TESTS; i++) {
    t1 = clock();
      Solution solution = heuristic->run();
    t2 = clock();

    times.set(t1, t2);
    objs.set(solution.getObjective(), i);
  }

  delete heuristic;

  times.average /= NUMBER_OF_TESTS;
  objs.average /= NUMBER_OF_TESTS;

  writeResults(inputPath, objs, times, input.k);
}

void Experiments::writeResults(string inputPath, Objectives objs, Times times, int k) {
  std::ofstream outFile(inputPath, std::ios_base::app);

  outFile << inputPath << "\t";
  outFile << k << "\t";
  outFile << times.average << "\t" << objs.average << "\t";
  outFile << objs.worst << "\t" << objs.best << "\n";

  outFile.close();

}
