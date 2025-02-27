#include "heuristic_tester.h"
#include "../data_structures/partialSolution.h"
#include "../data_structures/tabu.h"
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
    vector<Heuristic *> heuristics = {ils1, ils2, ils3, ils4};

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
