#include <iostream>
#include <filesystem>

#include "data_structures/input.h"
#include "helpers/random_utils.h"
#include "helpers/paremeter_tester.h"
#include "partialExperiments.h"

int nonImprovementsThreshold = 0;
int tabuTenure = 0;
bool useTabu = false;
bool useLocalSearchRand = false;

const string path = "../instances/preliminaries/";

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  seed();

  ParameterTester tester("random22.txt", RANDOM_LS_TWO);
  for (const auto & file: fs::directory_iterator(path)) {
    if (file.exists()) {
      std::cout << file.path().filename() << "\n";
      tester.testFile(file);
    }
  }

  return 0;
}
