#include <iostream>
#include <filesystem>
#include <random>
#include <algorithm>

#include "data_structures/input.h"
#include "helpers/heuristic_tester.h"
#include "heuristics/ils.h"
#include "heuristics/greedy.h"
#include "heuristics/grasp/grasp.h"
#include "helpers/random_utils.h"
#include "helpers/results_recorder.h"
#include "heuristics/tabu.h"

// #define TEST
// #define TEST_SINGLE
// #define PRELIMINARIES

int nonImprovementsThreshold = 0;

const string path = "../instances/";

void testSingle() {
  string file = path + "type2/classe_1_100_80.txt";
  bool resolve = false;
  Input* input = new Input(file, &resolve);

  tabu = Tabu(input->quantityOfSubsets);
  // tabu.setTabu(0, 10);
  // tabu.setTabu(3, 10);
  // tabu.setTabu(8, 10);
  // tabu.print();
  Ils ils(input);
  Solution sol = ils.run();

  // sol.print();

  // std::cout << "\ngreedy: \n";
  // GreedyKInter kinter(input);
  // kinter.run();
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

  // HeuristicTester greedyExperiments("results_kinter.txt", kInterFactory);
  HeuristicTester ilsExperiments("results_ils.txt", ILS);
  HeuristicTester graspExperiments("results_grasp.txt", GRASP_REACTIVE);

  #ifdef TEST_SINGLE 
    testSingle();
  #else

  for (const string dir: dirs) {
    for (const auto & file: fs::directory_iterator(path + dir)) {
      if (file.exists()) {
        // std::cout << file.path() << "\n";
        ilsExperiments.testFile(file);
      }
    }
  }

  #endif

  return 0;
}
