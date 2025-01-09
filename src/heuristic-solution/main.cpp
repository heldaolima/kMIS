#include "data_structures/input.h"
#include "dbg.h"
#include "helpers/heuristic_tester.h"
#include "helpers/random_utils.h"
#include "parse_arguments.h"
#include "partialExperiments.h"

#include <ctime>
#include <filesystem>
#include <iostream>
#include <map>

bool useTabu = false;

const string path = "../instances/";

namespace fs = std::filesystem;

void partialTest(const HeuristicTester &tester);
void ttt(HeuristicTester &tester);

int main(int argc, char *argv[]) {
  seed();

  HeuristicTester ilsExperiments = parseArguments(argc, argv);
  if (ilsExperiments.isTTT()) {
    ttt(ilsExperiments);
    return 0;
  }

#ifdef PARTIAL_TEST
  partialTest(ilsExperiments);
  return 0;
#else

  string dirs[3] = {"type1", "type2", "type3"};
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

void partialTest(const HeuristicTester &tester) {
  /*const std::vector<string> files = {*/
  /*    "type1/classe_1_40_40.txt",   "type1/classe_2_80_80.txt",*/
  /*    "type1/classe_3_140_140.txt", "type1/classe_4_200_200.txt",*/
  /*    "type1/classe_5_300_300.txt", "type1/classe_6_60_60.txt",*/
  /*    "type1/classe_7_240_240.txt", "type1/classe_8_100_100.txt",*/
  /*    "type1/classe_9_180_180.txt", "type1/classe_1_280_280.txt",*/
  /*    "type1/classe_2_40_40.txt",   "type1/classe_3_300_300.txt",*/
  /*    "type2/classe_1_40_32.txt",   "type2/classe_2_60_48.txt",*/
  /*    "type2/classe_3_100_80.txt",  "type2/classe_4_140_112.txt",*/
  /*    "type2/classe_5_200_160.txt", "type2/classe_6_300_240.txt",*/
  /*    "type2/classe_7_80_64.txt",   "type2/classe_8_240_192.txt",*/
  /*    "type2/classe_9_180_144.txt", "type2/classe_1_280_224.txt",*/
  /*    "type2/classe_2_300_240.txt", "type2/classe_3_40_32.txt",*/
  /*    "type3/classe_1_32_40.txt",   "type3/classe_2_48_60.txt",*/
  /*    "type3/classe_3_80_100.txt",  "type3/classe_4_112_140.txt",*/
  /*    "type3/classe_5_160_200.txt", "type3/classe_6_192_240.txt",*/
  /*    "type3/classe_7_224_280.txt", "type3/classe_8_240_300.txt",*/
  /*    "type3/classe_9_64_80.txt",   "type3/classe_1_144_180.txt",*/
  /*    "type3/classe_2_80_100.txt",  "type3/classe_3_240_300.txt"};*/

  const std::vector<string> files = {"type1/classe_1_100_100.txt"};

  const string path = "../instances/";
  for (const string filename : files) {
    const auto &file = fs::directory_entry(path + filename);
    if (file.exists()) {
      std::cout << file.path().filename() << "\n";
      tester.testFile(file);
    }
  }
}

void ttt(HeuristicTester &tester) {
  const string path = "../instances/";
  const std::map<string, int> instance_target = {
      {"type2/classe_6_240_192.txt", 3},
      {"type2/classe_8_300_240.txt", 9},
      {"type3/classe_4_32_40.txt", 25},
      {"type1/classe_9_80_80.txt", 65}};

  for (auto it : instance_target) {
    const auto &file = fs::directory_entry(path + it.first);
    if (file.exists()) {
      std::cout << file.path().filename() << "\n";
      tester.testTTT(file, it.second);
    }
  }
}
