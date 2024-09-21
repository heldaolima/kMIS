#include "heuristic_tester.h"
#include "../data_structures/partialSolution.h"
#include "../data_structures/tabu.h"
#include "../dbg.h"
#include "tester.h"
#include <ctime>

void HeuristicTester::testFile(const fs::directory_entry &inputFile) {
  Objectives objs;
  Times times;
  clock_t t1, t2;

  bool solvable = true;

  const Input *input = new Input(inputFile.path(), &solvable);

  if (solvable) {
    Heuristic *heuritic = heuristicFactory.createIls(input, *lsFactory);
    partialSolutions = PartialSolution(input);

    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
      tabu = Tabu(input->quantityOfSubsets);
      partialSolutions = PartialSolution(input);

      std::cout << "run " << i + 1 << "\n";
      t1 = clock();
      Solution solution;
      t2 = clock();

      times.set(t1, t2);
      times.setTimeToFindBest(solution.timeFound);
      objs.set(solution.getObjective(), solution.getIterationFound(), i);
    }

    times.avgTimeToFindBest /= NUMBER_OF_TESTS;
    times.average /= NUMBER_OF_TESTS;
    objs.average /= NUMBER_OF_TESTS;
    objs.averageFound /= NUMBER_OF_TESTS;

    writer->writeResults(inputFile.path().stem(), objs, times, input->k);

    /*delete heuristic;*/
    delete input;
  }
}
