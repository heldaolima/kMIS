#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "heuristics/ils.h"
#include "heuristics/greedy.h"
#include "heuristics/grasp/grasp.h"
#include "heuristics/local_search.h"
#include "helpers/random_utils.h"
#include "helpers/results_recorder.h"
#include "dbg.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  seed();

  string path = "../instances/";
  string dirs[1] = {"test"};
  // string dirs[3] = {"type1", "type2", "type3"};

  GreedyKInterFactory* kInterFactory = new GreedyKInterFactory;
  IlsFactory* ilsFactory = new IlsFactory;
  Grasp_ReactiveFactory* graspFactory = new Grasp_ReactiveFactory;

  Experiments greedyExperiments("results_kinter.txt", kInterFactory);
  Experiments ilsExperiments("results_ils.txt", ilsFactory);
  Experiments graspExperiments("results_grasp.txt", graspFactory);

  for (const string dir: dirs) {
    for (const auto & file: fs::directory_iterator(path + dir)) {

      // greedyExperiments.testHeuristic(file);
      ilsExperiments.testHeuristic(file);
      // graspExperiments.testHeuristic(file);
    }
  }
  
  delete kInterFactory;
  delete ilsFactory;
  delete graspFactory;

  return 0;
}
