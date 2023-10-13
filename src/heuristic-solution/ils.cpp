#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <time.h>

#include "heuristics/ils.h"
#include "heuristics/greedy.h"
#include "heuristics/grasp/grasp.h"
#include "random_utlis.h"
#include "dbg.h"

using std::ofstream, std::string;
namespace fs = std::filesystem;

#define NUMBER_OF_TESTS 10

const string header = "input\tk\tavg_time\tavg_objective\tworst\tbest\n";
const string ilsResultsFileName = "results_ils.txt";
const string greedyResultsFileName = "results_kinter.txt";
const string graspResultsFileName = "results_grasp.txt";

typedef struct objectives {
  int current = 0, best = 0, worst = 0;
  double average = 0.0;
  vector<int> eachOne;

  void set(int objective, int iteration) {
    current = objective;
    average += objective;
    eachOne.push_back(objective);

    if (iteration == 0) {
      best = current;
      worst = current;
    } 
    else {
      if (current > best) 
        best = current;
      if (current < worst)
        worst = current;
    }
  }

} Objectives;

typedef struct times {
  double current = 0.0, average = 0.0;
  vector<double> eachOne;

  void set(clock_t t1, clock_t t2) {
    current = (t2 - t1) / (double) CLOCKS_PER_SEC;
    average += current;
    eachOne.push_back(current);
  }

} Times;

void writeToFile(const string path, Objectives objs, Times times, int k, string input) {
  ofstream outFile(path, std::ios_base::app);

  outFile << input << "\t";
  outFile << k << "\t";
  outFile << times.average << "\t" << objs.average << "\t";
  outFile << objs.worst << "\t" << objs.best << "\n";

  outFile.close();
}

void graspRecordResults(string path) {
  Objectives objs;
  Times times;
  clock_t t1, t2;

  Input input(path);
  for (int i = 0; i < NUMBER_OF_TESTS; i++) {
    t1 = clock();
      Solution solution = reactiveGrasp(input);
    t2 = clock();

    times.set(t1, t2);
    objs.set(solution.getObjective(), i);
  }

  times.average /= NUMBER_OF_TESTS;
  objs.average /= NUMBER_OF_TESTS;

  writeToFile(graspResultsFileName, objs, times, input.k, path);
}

void greedyRecordResults(string path) {
  Objectives objs;
  Times times;
  clock_t t1, t2;

  Input input(path);
  for (int i = 0; i < NUMBER_OF_TESTS; i++) {
    t1 = clock();
      Solution solution = greedySolution(input);
    t2 = clock();

    times.set(t1, t2);
    objs.set(solution.getObjective(), i);
  }

  times.average /= NUMBER_OF_TESTS;
  objs.average /= NUMBER_OF_TESTS;

  writeToFile(greedyResultsFileName, objs, times, input.k, path);
}

void ilsRecordResulsts(string path) {
  Objectives objs;
  Times times;
  clock_t t1, t2;

  Input input(path);
  Ils heuristic(input);
  for (int i = 0; i < NUMBER_OF_TESTS; i++) {
    t1 = clock();
      Solution solution = heuristic.ils();
    t2 = clock();

    times.set(t1, t2);
    objs.set(solution.getObjective(), i);
  }

  times.average /= NUMBER_OF_TESTS;
  objs.average /= NUMBER_OF_TESTS;

  writeToFile(ilsResultsFileName, objs, times, input.k, path);
}

int main(int argc, char* argv[]) {
  seed();

  string path = "../instances/";
  string dirs[3] = {"type1", "type2", "type3"};

  ofstream ilsOutFile(ilsResultsFileName, std::ofstream::out);
  {
    ilsOutFile << header;
    ilsOutFile.close();
  }

  ofstream greedyOutFile(greedyResultsFileName, std::ofstream::out); 
  {
    greedyOutFile << header;
    greedyOutFile.close();
  }

  ofstream graspOutFile(graspResultsFileName, std::ofstream::out);
  {
    graspOutFile << header;
    graspOutFile.close();
  }

  for (const string dir: dirs) {
    for (const auto & file: fs::directory_iterator(path + dir)) {
      const string path = file.path().string();
      std::cout << path << "\n";

      ilsRecordResulsts(path);
      greedyRecordResults(path);
      graspRecordResults(path);
    }
  }

  return 0;
}
