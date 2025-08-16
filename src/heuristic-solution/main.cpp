#include "data_structures/input.h"
#include "helpers/heuristic_tester.h"
#include "helpers/random_utils.h"
#include "load_ttt_files.h"
#include "parse_arguments.h"
#include "partialExperiments.h"

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>

bool useTabu = false;

namespace fs = std::filesystem;

vector<string> loadFiles(const string& path) {
  vector<string> files;
  std::ifstream file(path);
  if (!file) {
    std::cerr << "Error opening instances file\n";
    return files;
  }

  string filename;
  while (file >> filename) {
    files.push_back(filename);
  }

  file.close();

  return files;
}

int main(int argc, char *argv[]) {
  std::cout << "hallo\n";

  seed();

  const string path = "../instances/";

  HeuristicTester ilsExperiments = parseArguments(argc, argv);

  if (ilsExperiments.isPartial()) {
    const string instancesFile = "selected_instances.txt";
    auto instances = loadFiles(instancesFile);
    for (const auto filename: instances) {
      const auto &file = fs::directory_entry(filename);
      if (file.exists()) {
        std::cout << file.path().filename() << "\n";
        ilsExperiments.testPartial(file);
      }
    }
    return 0;
  }


  // run time-to-target experiment
  if (ilsExperiments.isTTT()) {
    const string instances_file = "ttt_instances.txt";
    std::map<string, int> instances = load_ttt_files(instances_file);

    for (const auto &[filename, target] : instances) {
      const auto &file = fs::directory_entry(path + filename);
      if (file.exists() && file.path().filename().string()[0] != '#') {
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
