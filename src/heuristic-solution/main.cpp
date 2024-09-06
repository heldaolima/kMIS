#include <ctime>
#include <filesystem>
#include <iostream>

#include "data_structures/input.h"
#include "helpers/heuristic_tester.h"
#include "helpers/random_utils.h"
#include "partialExperiments.h"

bool useTabu = false;
bool useLocalSearchRand = false;

const string path = "../instances/";

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  seed();

  string dirs[3] = {"type1", "type2", "type3"};

  /*HeuristicTester ilsExperiments("test_time.csv", ILS_TIME);*/

  for (const string dir : dirs) {
    for (const auto &file : fs::directory_iterator(path + dir)) {
      if (file.exists()) {
        std::cout << file.path().filename() << "\n";
        /*ilsExperiments.testFile(file);*/
      }
    }
  }

  return 0;
}
