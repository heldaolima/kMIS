#include "heuristic_tester.h"
#include "../data_structures/partialSolution.h"
#include "../data_structures/tabu.h"
#include "../heuristics/perturb_strategies/get_number_strategies/get_number_to_remove_strategy.h"
#include "tester.h"
#include <ctime>

void HeuristicTester::testFile(const fs::directory_entry &inputFile) const {
  bool solvable = true;
  const Input *input = new Input(inputFile.path().string(), &solvable);

  if (solvable) {
    Objectives objs;
    Times times;
    clock_t t1, t2;

    Heuristic *heuristic = heuristicFactory.createIls(
        input, *lsFactory, *perturbationFactory, acceptanceFactory);
    heuristic->print();

    for (int i = 0; i < numberOfTests; i++) {
      tabu = Tabu(input->quantityOfSubsets);
      partialSolutions = PartialSolution(input);

      Solution actual(input->quantityOfSubsets);
      std::cout << "Running [" << i + 1 << "]\n";
      t1 = clock();
      Solution solution = heuristic->run();
      t2 = clock();

      times.set(t1, t2);
      times.setTimeToFindBest(solution.timeFound);
      objs.set(solution.getObjective(), solution.getIterationFound(), i);
    }

    times.avgTimeToFindBest /= NUMBER_OF_TESTS;
    times.average /= NUMBER_OF_TESTS;
    objs.average /= NUMBER_OF_TESTS;
    objs.averageFound /= NUMBER_OF_TESTS;

    writer.writeResults(inputFile.path().stem().string(), objs, times, input->k);

    delete heuristic;
    delete input;
  }
}

bool HeuristicTester::isTTT() { return ttt; }

void HeuristicTester::setTTT() { ttt = true; }

void HeuristicTester::testTTT(const fs::directory_entry &inputFile,
                              int target) {

  bool solvable = true;
  const Input *input = new Input(inputFile.path().string(), &solvable);

  if (solvable) {
    heuristicFactory.setTarget(target);

    map<string, Heuristic*> heuristics;
    heuristics["ILS-1"] = heuristicFactory.ttt_createILS1(input);
    heuristics["ILS-2"] = heuristicFactory.ttt_createILS2(input);
    // heuristics["ILS-3"] = heuristicFactory.ttt_createILS3(input);
    heuristics["ILS-4"] = heuristicFactory.ttt_createILS4(input);

    map<string, vector<double>> results;
    results["ILS-1"] = {};
    results["ILS-2"] = {};
    // results["ILS-3"] = {};
    results["ILS-4"] = {};

    for (const auto &h : heuristics){ 
      h.second->print();
      vector<Times> times;
      for (int i = 0; i < numberOfTestsTTT; i++) {
        Times times;
        clock_t t1, t2;

        tabu = Tabu(input->quantityOfSubsets);
        partialSolutions = PartialSolution(input);

        std::cout << "Running [" << i + 1 << "]\n";
        t1 = clock();
          Solution solution = h.second->run();
        t2 = clock();

        times.set(t1, t2);
        results[h.first].push_back(times.current);
        std::cout << "Time found: " << times.current << "\n";
      }
      writer.writeGlobalTTT(inputFile.path().stem().string(), h.first, results[h.first]);
    }
    writer.writeInstanceTTT(inputFile.path().stem().string(), results, target);

    for (const auto &h : heuristics){ 
      delete h.second;
    }

    delete input;
  }
}

bool HeuristicTester::isPartial()  {
  return partial;
}

void HeuristicTester::setPartial() {
  partial = true;
}


void HeuristicTester::testPartial(const fs::directory_entry &inputFile) {

  bool solvable = true;
  const Input *input = new Input(inputFile.path().string(), &solvable);

  map<NumberToRemoveEstrategyEnum, string> strategies;
  strategies[FLOOR_ROOT_OF_K] = "partial_results/floor_root_k.csv";
  strategies[CEIL_ROOT_OF_K] = "partial_results/ceil_root_k.csv";
  strategies[RANDOM_PROPORTION] = "partial_results/random_proportion.csv";
  strategies[FLOOR_LOG] = "partial_results/floor_log.csv";
  strategies[CEIL_LOG] = "partial_results/ceil_log.csv";

  map<NumberToRemoveEstrategyEnum, string> strategiesDetailed;
  strategiesDetailed[FLOOR_ROOT_OF_K] = "partial_results/floor_root_k_detailed.csv";
  strategiesDetailed[CEIL_ROOT_OF_K] = "partial_results/ceil_root_k_detailed.csv";
  strategiesDetailed[RANDOM_PROPORTION] = "partial_results/random_proportion_detailed.csv";
  strategiesDetailed[FLOOR_LOG] = "partial_results/floor_log_detailed.csv";
  strategiesDetailed[CEIL_LOG] = "partial_results/ceil_log_detailed.csv";

  if (solvable) {
    map<NumberToRemoveEstrategyEnum, Heuristic*> heuristics;

    for (const auto &strategy: strategies) {
      heuristics[strategy.first] = heuristicFactory.createWithPerturbStrategy(input, strategy.first);
    }

    for (const auto &h: heuristics) {
      h.second->print();
      Times times;
      Objectives objs;
      for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        clock_t t1, t2;

        tabu = Tabu(input->quantityOfSubsets);
        partialSolutions = PartialSolution(input);

        std::cout << "Running [" << i + 1 << "]\n";
        t1 = clock();
        Solution solution = h.second->run();
        t2 = clock();
        solution.print();

        times.set(t1, t2);
        times.setTimeToFindBest(solution.timeFound);
        objs.set(solution.getObjective(), solution.getIterationFound(), i);
        std::cout << "Time found: " << times.current << " | Obj:" << solution.getObjective() << "\n";
        writer.writePartialDetailed(inputFile.path().stem().string(), strategiesDetailed[h.first], times.current, solution.getObjective());
      }

      times.avgTimeToFindBest /= NUMBER_OF_TESTS;
      times.average /= NUMBER_OF_TESTS;
      objs.average /= NUMBER_OF_TESTS;
      objs.averageFound /= NUMBER_OF_TESTS;

      writer.writePartial(inputFile.path().stem().string(), strategies[h.first], times, objs);
    }

    for (const auto &h: heuristics) {
      delete h.second;
    }

    delete input;
  }
}
