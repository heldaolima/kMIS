#include "paremeter_tester.h"
#include "../data_structures/input.h"
#include "results_writer.h"
#include <sstream>
#include "../heuristic_factory.h"
#include "../partialExperiments.h"
#include "../dbg.h"
#include "../heuristics/tabu.h"

const string header = "input,k,avg_time,avg_objective,avg_it_best,worst,best\n";

ParameterTester::ParameterTester(string outputPath, ParametersEnum param) {
  this->writer = new ResultsWriter(outputPath, header);
  this->param = param;
}

void ParameterTester::testFile(fs::directory_entry inputFile) {
  switch (param) {
    case RESTART_THRESHOLD: testRestart(&inputFile); break;
    case TABU_TENURE: testTenure(&inputFile); break;
    case RANDOM_LS_TWO: lsTwo(&inputFile, true); break;
    case NORMAL_LS_TWO: lsTwo(&inputFile, false); break;
    case RANDOM_LS_TWO_TABU: testRandomLSTwoTabu(&inputFile); break;
    default: break;
  }
}

void ParameterTester::testRestart(fs::directory_entry *inputFile) {
  Objectives objs;
  Times times;
  clock_t t1, t2;

  bool solvable = true;
  Input* input = new Input(inputFile->path(), &solvable);
  vector<int> tests = { 10, 25, 50, 75, 100, 125, 150 };

  std::stringstream ss;
  if (solvable) {
    Heuristic* heuristic = HeuristicFactory::create(input, ILS);
    for (int test: tests) {
      nonImprovementsThreshold = test;
      debug("testing threshold %d", test);

      for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        tabu = Tabu(input->quantityOfSubsets);
        t1 = clock();
          Solution solution = heuristic->run();
        t2 = clock();

        times.set(t1, t2);
        objs.set(solution.getObjective(), solution.getIterationFound(), i);
      }

      times.average /= NUMBER_OF_TESTS;
      objs.average /= NUMBER_OF_TESTS;
      objs.averageFound /= NUMBER_OF_TESTS;
      
      ss << inputFile->path().filename().string() << "_" << test;
      writer->writeResults(ss.str(), objs, times, input->k);
      ss.str("");
    }

    delete heuristic;
    delete input;
  }
}

void ParameterTester::testTenure(fs::directory_entry *inputFile) {
  Objectives objs;
  Times times;
  clock_t t1, t2;

  bool solvable = true;
  Input* input = new Input(inputFile->path(), &solvable);
  vector<int> tests = { 5, 10, 25, 50 };
  std::stringstream ss;
  if (solvable) {
    Heuristic* heuristic = HeuristicFactory::create(input, ILS);
    for (int test: tests) {
      tabuTenure = test;
      debug("testing tenure %d", test);

      for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        tabu = Tabu(input->quantityOfSubsets);
        t1 = clock();
          Solution solution = heuristic->run();
        t2 = clock();

        times.set(t1, t2);
        objs.set(solution.getObjective(), solution.getIterationFound(), i);
      }

      times.average /= NUMBER_OF_TESTS;
      objs.average /= NUMBER_OF_TESTS;
      objs.averageFound /= NUMBER_OF_TESTS;
      
      ss << inputFile->path().filename().string() << "_" << test;
      writer->writeResults(ss.str(), objs, times, input->k);
      ss.str("");
    }

    delete heuristic;
    delete input;
  }
}

void ParameterTester::lsTwo(fs::directory_entry* inputFile, bool random) {
  Objectives objs;
  Times times;
  clock_t t1, t2;

  bool solvable = true;
  Input* input = new Input(inputFile->path(), &solvable);

  if (random)
    debug("testing random local search swap(2,2)");
  else
    debug("testing normal local search swap(2, 2)");

  useLocalSearchRand = random;

  if (solvable) {
    Heuristic* heuristic = HeuristicFactory::create(input, ILS);

    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
      tabu = Tabu(input->quantityOfSubsets);
      t1 = clock();
        Solution solution = heuristic->run();
      t2 = clock();

      times.set(t1, t2);
      objs.set(solution.getObjective(), solution.getIterationFound(), i);
    }

    times.average /= NUMBER_OF_TESTS;
    objs.average /= NUMBER_OF_TESTS;
    objs.averageFound /= NUMBER_OF_TESTS;

    writer->writeResults(inputFile->path().filename().string(), objs, times, input->k);

    delete heuristic;
    delete input;
  }
}

void ParameterTester::lsTwoTabu(fs::directory_entry* inputFile, bool random) {
  Objectives objs;
  Times times;
  clock_t t1, t2;

  bool solvable = true;
  Input* input = new Input(inputFile->path(), &solvable);

  if (random)
    debug("testing tabu random local search swap(2,2)");
  else
    debug("testing tabu normal local search swap(2, 2)");

  useLocalSearchRand = random;

  if (solvable) {
    Heuristic* heuristic = HeuristicFactory::create(input, ILS);

    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
      tabu = Tabu(input->quantityOfSubsets);
      t1 = clock();
        Solution solution = heuristic->run();
      t2 = clock();

      times.set(t1, t2);
      objs.set(solution.getObjective(), solution.getIterationFound(), i);
    }

    times.average /= NUMBER_OF_TESTS;
    objs.average /= NUMBER_OF_TESTS;
    objs.averageFound /= NUMBER_OF_TESTS;

    writer->writeResults(inputFile->path().filename().string(), objs, times, input->k);

    delete heuristic;
    delete input;
  }
}
void ParameterTester::testRandomLSTwoTabu(fs::directory_entry* inputFile) {
  Objectives objs;
  Times times;
  clock_t t1, t2;

  bool solvable = true;
  Input* input = new Input(inputFile->path(), &solvable);

  debug("testing random local search swap(2,2) tabu");
  useLocalSearchRand = true;
  useTabu = true;

  if (solvable) {
    Heuristic* heuristic = HeuristicFactory::create(input, ILS);

    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
      tabu = Tabu(input->quantityOfSubsets);
      t1 = clock();
        Solution solution = heuristic->run();
      t2 = clock();

      times.set(t1, t2);
      objs.set(solution.getObjective(), solution.getIterationFound(), i);
    }

    times.average /= NUMBER_OF_TESTS;
    objs.average /= NUMBER_OF_TESTS;
    objs.averageFound /= NUMBER_OF_TESTS;

    writer->writeResults(inputFile->path().filename().string(), objs, times, input->k);

    delete heuristic;
    delete input;
  }

}
