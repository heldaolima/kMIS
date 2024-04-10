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

const string path = "../instances/worsts/";

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  seed();

  // ParameterTester rand("random22.csv", RANDOM_LS_TWO);
  // ParameterTester norm("normal22.csv", NORMAL_LS_TWO);
  ParameterTester t1("random22x2Tabu.csv", RANDOM_LS_TWO_TABU);
  ParameterTester t2("random22x2.csv", RANDOM_LS_TWO);
  for (const auto & file: fs::directory_iterator(path)) {
    if (file.exists()) {
      std::cout << file.path().filename() << "\n";
      t1.testFile(file);
      t2.testFile(file);
    }
  }

  return 0;
}
