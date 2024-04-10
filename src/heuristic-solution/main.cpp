#include <filesystem>

#include "data_structures/input.h"
#include "helpers/heuristic_tester.h"
#include "heuristics/ils.h"
#include "helpers/random_utils.h"
#include "heuristics/tabu.h"
#include "partialExperiments.h"

// #define TEST
// #define TEST_SINGLE
// #define PRELIMINARIES

int nonImprovementsThreshold = 75;
int tabuTenure = 5;
bool useTabu = true;
bool useLocalSearchRand = true;

const string path = "../instances/";

void testSingle(string test) {
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
