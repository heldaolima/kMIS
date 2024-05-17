#include "ils_time.h"
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

Solution IlsTime::run() {
  clock_t t1 = clock(), t2 = clock();
  constructionArrays auxArrays;
  int idxAlpha = auxArrays.getIdxAlpha();
  double alpha = X[idxAlpha];

  RestartSolution restart(input);

  ExtendedKInter greedy(input);
  greedy.setTime(t1);
  Solution best = greedy.run();

  LocalSearch(best, 0, t1);
  Solution globalBest = best;
  globalBest.timeFound = best.timeFound;

  restart.setSubsetAsUsed(best.subsetsInSolution[0]);
  int iteration = 1;
  int iterationsWithoutImprovement = 0;

  Solution currentSolution;
  double elapsedTime = globalBest.timeFound;
  while (elapsedTime <= (double)input->k / 10) {
    // debug("iteration=%d", iteration);
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

    t2 = clock();
    iteration++;

    elapsedTime = (t2 - t1) / (double) CLOCKS_PER_SEC;
  }

  return globalBest;
}

Solution IlsTime::Construction(RestartSolution *restart) {
  GreedyKInter kInter(input);
  kInter.setRestart(restart);
  return kInter.run();
}

Solution IlsTime::Construction(double alpha) {
  return grasp_construction(input, alpha);
}

Solution IlsTime::Construction() { 
  return ExtendedKInter().run(); 
}

Solution IlsTime::Perturbation(Solution *solution, double alpha) {
  return perturbReactive(*solution, input, alpha);
}

void IlsTime::LocalSearch(Solution &solution, int iteration, clock_t t1) {
  vnd(input, solution, iteration, t1);
}
