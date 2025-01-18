#include "heuristic_tester.h"
#include "../data_structures/partialSolution.h"
#include "../data_structures/tabu.h"
#include "../dbg.h"
#include "random_utils.h"
#include "tester.h"
#include <ctime>

void HeuristicTester::testFile(const fs::directory_entry &inputFile) const {
  bool solvable = true;
  const Input *input = new Input(inputFile.path(), &solvable);

  if (solvable) {
    Objectives objs;
    Times times;
    clock_t t1, t2;

    Heuristic *heuristic =
        heuristicFactory.createIls(input, *lsFactory, *perturbationFactory);

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
    Heuristic *heuristic =
        heuristicFactory.createIls(input, *lsFactory, *perturbationFactory);
    heuristic->print();

    for (int i = 0; i < numberOfTestsTTT; i++) {
      seed();
      Times times;
      clock_t t1, t2;

      tabu = Tabu(input->quantityOfSubsets);
      partialSolutions = PartialSolution(input);

      std::cout << "Running [" << i + 1 << "]\n";
      t1 = clock();
      Solution solution = heuristic->run();
      t2 = clock();
      solution.print();

      times.set(t1, t2);
      writer.writeTTT(inputFile.path().stem(), heuristic->toString(), times);
    }

    delete heuristic;
    delete input;
  }
}
