#include "data_structures/input.h"
#include "helpers/heuristic_tester.h"
#include "helpers/random_utils.h"
#include "load_ttt_files.h"
#include "parse_arguments.h"
#include "partialExperiments.h"

#include <ctime>
#include <filesystem>
#include <iostream>
#include <map>

bool useTabu = false;

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  seed();

  const string path = "../instances/";

  HeuristicTester ilsExperiments = parseArguments(argc, argv);

  // run time-to-target experiment
  if (ilsExperiments.isTTT()) {
    const string instances_file = "ttt_instances.txt";
    std::map<string, int> instances = load_ttt_files(instances_file);

    for (const auto &[filename, target] : instances) {
      const auto &file = fs::directory_entry(path + filename);
      if (file.exists()) {
        std::cout << file.path().filename() << " | " << target << "\n";
        ilsExperiments.testTTT(file, target);
      }
    }

    return 0;
  }

  // run normal experiment
  string dirs[3] = {"type1", "type2", "type3"};
  for (const string dir : dirs) {
    for (const auto &file : fs::directory_iterator(path + dir)) {
      if (file.exists()) {
        std::cout << file.path().filename() << "\n";
        ilsExperiments.testFile(file);
      }
    }
  }

  return 0;
}
