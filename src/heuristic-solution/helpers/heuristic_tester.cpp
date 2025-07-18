#include "heuristic_tester.h"
#include "../data_structures/partialSolution.h"
#include "../data_structures/tabu.h"
#include "../heuristics/perturb_strategies/get_number_strategies/get_number_to_remove_strategy.h"
#include "tester.h"
#include <ctime>

void HeuristicTester::testFile(const fs::directory_entry &inputFile) const {
  bool solvable = true;
  const Input *input = new Input(inputFile.path(), &solvable);

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

    writer.writeResults(inputFile.path().stem(), objs, times, input->k);

    delete heuristic;
    delete input;
  }
}

bool HeuristicTester::isTTT() { return ttt; }

void HeuristicTester::setTTT() { ttt = true; }

void HeuristicTester::testTTT(const fs::directory_entry &inputFile,
                              int target) {

  bool solvable = true;
  const Input *input = new Input(inputFile.path(), &solvable);

  if (solvable) {
    heuristicFactory.setTarget(target);

    Heuristic *ils1 = heuristicFactory.ttt_createILS1(input);
    Heuristic *ils2 = heuristicFactory.ttt_createILS2(input);
    Heuristic *ils3 = heuristicFactory.ttt_createILS3(input);
    Heuristic *ils4 = heuristicFactory.ttt_createILS4(input);
    vector<Heuristic *> heuristics = {
      ils1, 
      ils2, 
      // ils3, 
      ils4
    };

    for (auto h : heuristics) {
      h->print();
      for (int i = 0; i < numberOfTestsTTT; i++) {
        Times times;
        clock_t t1, t2;

        tabu = Tabu(input->quantityOfSubsets);
        partialSolutions = PartialSolution(input);

        std::cout << "Running [" << i + 1 << "]\n";
        t1 = clock();
        Solution solution = h->run();
        t2 = clock();
        solution.print();

        times.set(t1, t2);
        std::cout << "Time found: " << times.current << "\n";
        writer.writeTTT(inputFile.path().stem(), h->toString(), times, target);
      }
    }

    delete ils1;
    delete ils2;
    delete ils3;
    delete ils4;
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
  const Input *input = new Input(inputFile.path(), &solvable);

  vector<NumberToRemoveEstrategyEnum> strategies = {
    ROOT_OF_K,
    CEIL_ROOT_OF_K,
    RANDOM_PROPORTION,
    FLOOR_LOG,
    CEIL_LOG,
  };

  vector<string> outputs = {
    "partial_results/floor_root_k.csv",
    "partial_results/ceil_root_k.csv",
    "partial_results/random_proportion.csv",
    "partial_results/floor_log.csv",
    "partial_results/ceil_log.csv"
  };

  if (solvable) {
    vector<Heuristic*> heuristics;
    for (auto strategy: strategies) {
      heuristics.push_back(heuristicFactory.createWithPerturbStrategy(input, strategy));
    }

    for (int h = 0; h < heuristics.size(); h++) {
      heuristics[h]->print();
      Times times;
      Objectives objs;
      for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        clock_t t1, t2;

        tabu = Tabu(input->quantityOfSubsets);
        partialSolutions = PartialSolution(input);

        std::cout << "Running [" << i + 1 << "]\n";
        t1 = clock();
        Solution solution = heuristics[h]->run();
        t2 = clock();
        solution.print();

        times.set(t1, t2);
        times.setTimeToFindBest(solution.timeFound);
        objs.set(solution.getObjective(), solution.getIterationFound(), i);
        std::cout << "Time found: " << times.current << "\n";
      }

      times.avgTimeToFindBest /= NUMBER_OF_TESTS;
      times.average /= NUMBER_OF_TESTS;
      objs.average /= NUMBER_OF_TESTS;
      objs.averageFound /= NUMBER_OF_TESTS;

      writer.writePartial(inputFile.path().stem(), outputs[h], times, objs);
    }

    for (int i = 0; i < heuristics.size(); i++) {
      delete heuristics[i];
    }

    delete input;
  }
}
