#include <ctime>
#include <filesystem>
#include <iostream>

#include "data_structures/input.h"
#include "data_structures/partialSolution.h"
#include "dbg.h"
#include "helpers/heuristic_tester.h"
#include "helpers/random_utils.h"
#include "heuristics/kinter.h"
#include "heuristics/ils.h"
#include "heuristics/local_search.h"
#include "heuristics/perturb.h"
#include "heuristics/restart.h"
#include "heuristics/tabu.h"
#include "partialExperiments.h"
#include "heuristics/extended_kinter.h"
#include "heuristics/vnd.h"

// #define TEST_SINGLE
// #define PRELIMINARIES

int nonImprovementsThreshold = 75;
int tabuTenure = 5;
bool useTabu = false;
bool useLocalSearchRand = false;

const string path = "../instances/";

void testSingle(string test) {
  // clock_t t1, t2;
  // string file = path + test;
  // bool resolve = false;
  // Input *input = new Input(file,  &resolve);
  //
  // partialSolutions = PartialSolution(input);
  // Tabu tabu(input->quantityOfSubsets);

  // Ils ils(input);
  // t1 = clock();
  //   Solution s_ils = ils.run(t1);
  // t2 = clock();
  // std::cout << "\nfinal: \n";
  // s_ils.print();

  // std::cout << "ellapsed time: " << (t2 - t1) / (double) CLOCKS_PER_SEC << "\n";

  // LocalSearch ls = LocalSearch(input, 0);
  //
  // GreedyKInter greedy(input);
  // greedy.setRestart(&r);
  //
  // ExtendedKInter ext(input);
  // Solution s = ext.run();
  // std::cout << "\nMy extended: \n";
  // s.print();
  //
  // Solution x = greedy.run();
  // std::cout << "\nkInter: \n";
  // x.print();

  // delete input;
}

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  seed();

#ifdef TEST
  string dirs[1] = {"test"};
#else
  string dirs[3] = {"type1", "type2", "type3"};
#endif

  HeuristicTester ilsExperiments("test_time.csv", ILS);

#ifdef TEST_SINGLE
  testSingle(argv[1]);
#else

  for (const string dir : dirs) {
    for (const auto &file : fs::directory_iterator(path + dir)) {
      if (file.exists()) {
        std::cout << file.path().filename() << "\n";
        ilsExperiments.testFile(file);
      }
    }
  }

#endif

  return 0;
}
