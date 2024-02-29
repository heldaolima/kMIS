#include <iostream>
#include <filesystem>

#include "data_structures/input.h"
#include "heuristics/ils.h"
#include "heuristics/greedy.h"
#include "heuristics/grasp/grasp.h"
#include "helpers/random_utils.h"
#include "helpers/results_recorder.h"
#include "heuristics/restart.h"

// #define TEST
// #define TEST_SINGLE

const string path = "../instances/";

void testSingle() {
  string file = path + "test/classe_1_40_40.txt";
  std::cout << file << "\n";
  bool resolve = false;
  Input* input = new Input(file, &resolve);
  RestartSolution restart(input);
  std::cout << "restart:\n";
  restart.setSubsetAsUsed(4);
  restart.run();

  std::cout << "\ngreedy: \n";
  GreedyKInter kinter(input);
  kinter.run();
  delete input;
  // ilsExperiments.testHeuristic(fs::directory_entry(file));
}

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  seed();

  #ifdef TEST
  string dirs[1] = {"test"};
  #else
  string dirs[3] = { "type1", "type2", "type3" };
  #endif
  // string dirs[1] = {"type1"};

  GreedyKInterFactory* kInterFactory = new GreedyKInterFactory;
  IlsFactory* ilsFactory = new IlsFactory;
  Grasp_ReactiveFactory* graspFactory = new Grasp_ReactiveFactory;

  Experiments greedyExperiments("results_kinter.txt", kInterFactory);
  Experiments ilsExperiments("results_ils.txt", ilsFactory);
  Experiments graspExperiments("results_grasp.txt", graspFactory);

  #ifdef TEST_SINGLE 
    testSingle();
  #else
  for (const string dir: dirs) {
    for (const auto & file: fs::directory_iterator(path + dir)) {
      if (file.exists()) {
        std::cout << file.path() << "\n";
        ilsExperiments.testHeuristic(file);
        graspExperiments.testHeuristic(file);
        // greedyExperiments.testHeuristic(file);
      }
    }
  }
  #endif

  delete kInterFactory;
  delete ilsFactory;
  delete graspFactory;

  return 0;
}
