#include "heuristic_tester.h"
#include "../data_structures/partialSolution.h"
#include "../data_structures/tabu.h"
#include <ctime>
#include "../dbg.h"
#include "tester.h"

const string header = "input,k,best,worst,avg_obj,avg_time_to_best\n";

HeuristicTester::HeuristicTester(string outPath, HeuristicsEnum type) {
  this->writer = new ResultsWriter(outPath, header);
  this->type = type;
}

void HeuristicTester::testFile(fs::directory_entry inputFile) {
  Objectives objs;
  Times times;
  clock_t t1, t2;

  bool solvable = true;

  Input *input = new Input(inputFile.path(), &solvable);
  if (solvable) {
    Heuristic *heuristic = HeuristicFactory::create(input, type);
    partialSolutions = PartialSolution(input);

    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
      tabu = Tabu(input->quantityOfSubsets);
      partialSolutions = PartialSolution(input);

      std::cout << "run " << i + 1 << "\n";
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

    writer->writeResults(inputFile.path().stem(), &objs, &times, input->k);

    delete heuristic;
    delete input;
  }
}
