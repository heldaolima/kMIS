#include <filesystem>

#include "data_structures/input.h"
#include "data_structures/solutionMinusOne.h"
#include "dbg.h"
#include "helpers/heuristic_tester.h"
#include "heuristics/greedy.h"
#include "heuristics/ils.h"
#include "helpers/random_utils.h"
#include "heuristics/perturb.h"
#include "heuristics/restart.h"
#include "heuristics/tabu.h"
#include "partialExperiments.h"

// #define TEST
#define TEST_SINGLE
// #define PRELIMINARIES

int nonImprovementsThreshold = 75;
int tabuTenure = 5;
bool useTabu = true;
bool useLocalSearchRand = false;

const string path = "../instances/";

void testSingle(string test) {
  string file = path + test;
  bool resolve = false;
  Input* input = new Input(file, &resolve);

  minusOne = SolutionMinusOne(input);
  RestartSolution r = RestartSolution(input);

  GreedyKInter kinter(input);
  kinter.setRestart(&r);
  Solution s = kinter.run();

  perturbReactive(s, input, 0.4);



  // tabu = Tabu(input->quantityOfSubsets);
  //
  // Ils ils(input);
  // ils.run();

  delete input;
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
  HeuristicTester ilsExperiments("results_ils.csv", ILS);

  #ifdef TEST_SINGLE 
    testSingle(argv[1]);
  #else

  for (const string dir: dirs) {
    for (const auto & file: fs::directory_iterator(path + dir)) {
      if (file.exists()) {
        std::cout << file.path().filename() << "\n";
        ilsExperiments.testFile(file);
      }
    }
  }

  #endif

  return 0;
}
