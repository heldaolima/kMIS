#include "ils_iterations.h"
#include "../../dbg.h"
#include "../greedy/extended_kinter.h"
#include "../grasp/construction_arrays.h"
#include "../grasp/construction.h"
#include "../vnd.h"
#include "../perturb.h"
#include "../grasp/costs.h"
#include "../greedy/kinter.h"
#include "../restart.h"
#include "../../data_structures/tabu.h"
#include <ctime>

#define NON_IMPROVEMENTS_THRESHOLD 75
#define NUMBER_OF_ITERATIONS 500

Solution IlsIterations::run() {
  constructionArrays auxArrays;
  int idxAlpha = auxArrays.getIdxAlpha();
  double alpha = X[idxAlpha];

  RestartSolution restart(input);

  ExtendedKInter greedy(input);
  greedy.setTime(clock());
  Solution best = greedy.run();

  LocalSearch(best, 0, t1);
  Solution globalBest = best;

  restart.setSubsetAsUsed(best.subsetsInSolution[0]);
  int iteration = 1;
  int iterationsWithoutImprovement = 0;

  Solution currentSolution;
  for (; iteration < NUMBER_OF_ITERATIONS; iteration++) {
    idxAlpha = auxArrays.getIdxAlpha();
    alpha = X[idxAlpha];

    currentSolution = Perturbation(&best, alpha);
    LocalSearch(currentSolution, iteration, t1);
    if (currentSolution.getObjective() > best.getObjective()) {
      best = currentSolution;
      best.setIterationFoud(iteration);

      if (best.getObjective() > globalBest.getObjective()) {
        globalBest = best;
        globalBest.setIterationFoud(iteration);
        std::cout << "\nNew global best (it= "<< iteration << "): ";
        globalBest.print();
      }

      iterationsWithoutImprovement = 0;
    } else {
      iterationsWithoutImprovement++;
    }

    if (iterationsWithoutImprovement > NON_IMPROVEMENTS_THRESHOLD) {
      best = restart.run(t1);

      LocalSearch(best, iteration, t1);
      if (best.getObjective() > globalBest.getObjective()) {
        globalBest = best;
        globalBest.setIterationFoud(iteration);
      }
      iterationsWithoutImprovement = 0;
    }

    auxArrays.computeIdxAlpha(idxAlpha, currentSolution.getObjective());

    if (iteration % TAM_X == 0)
      auxArrays.updateProbabilities(best.getObjective());

    iteration++;
  }

  return globalBest;
}


Solution IlsIterations::Construction(RestartSolution *restart) {
  GreedyKInter kInter(input);
  kInter.setRestart(restart);
  return kInter.run();
}

Solution IlsIterations::Construction(double alpha) {
  return grasp_construction(input, alpha);
}

Solution IlsIterations::Construction() { 
  return ExtendedKInter().run(); 
}

Solution IlsIterations::Perturbation(Solution *solution, double alpha) {
  return perturbReactive(*solution, input, alpha);
}

void IlsIterations::LocalSearch(Solution &solution, int iteration, clock_t t1) {
  vnd(input, solution, iteration, t1);
}
