#include <iostream>
#include <filesystem>

#include "data_structures/input.h"
#include "helpers/random_utils.h"
#include "helpers/paremeter_tester.h"
#include "partialExperiments.h"

int nonImprovementsThreshold = 0;

const string path = "../instances/preliminaries/";

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  seed();

  ParameterTester tester("", RESTART_THRESHOLD);
  for (const auto & file: fs::directory_iterator(path)) {
    if (file.exists()) {
      std::cout << file.path().filename() << "\n";
      tester.testFile(file);
    }
  }

  return 0;
}
