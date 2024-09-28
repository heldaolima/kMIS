#include "ils.h"
#include "grasp/construction.h"
#include "grasp/construction_arrays.h"
#include "grasp/costs.h"
#include "greedy/extended_kinter.h"
#include "greedy/kinter.h"
#include "perturb.h"
#include "restart.h"
#include <ctime>

Solution Ils::run() {
  clock_t t1 = clock(), t2 = clock();
  constructionArrays auxArrays;
  int idxAlpha = auxArrays.getIdxAlpha();
  double alpha = X[idxAlpha];

  RestartSolution restart(input);

  ExtendedKInter greedy(input);
  greedy.setTime(t1);
  Solution best = greedy.run();

  Vnd(best, 0, t1);
  Solution globalBest = best;
  globalBest.timeFound = best.timeFound;

  restart.setSubsetAsUsed(best.subsetsInSolution[0]);
  int iterationsWithoutImprovement = 0, iteration = 1;

  Solution currentSolution;
  stopStrategy->init();
  while (!stopStrategy->stopCondition()) {
    // debug("iteration=%d", iteration);
    idxAlpha = auxArrays.getIdxAlpha();
    alpha = X[idxAlpha];

    currentSolution = Perturbation(best, alpha);
    Vnd(currentSolution, iteration, t1);
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

    if (iterationsWithoutImprovement > restart.noImprovementsThreshold) {
      best = restart.run(t1);

      Vnd(best, iteration, t1);
      if (best.getObjective() > globalBest.getObjective()) {
        globalBest = best;
        globalBest.setIterationFoud(iteration);
      }
      iterationsWithoutImprovement = 0;
    }

    auxArrays.computeIdxAlpha(idxAlpha, currentSolution.getObjective());

    if (iteration % TAM_X == 0)
      auxArrays.updateProbabilities(best.getObjective());

    stopStrategy->update();
    iteration++;
  }
  return globalBest;
}

void Ils::Vnd(Solution &solution, int iteration, clock_t t1) {
  int it = 1;
  clock_t t2 = clock();
  bool improved;

  Solution copy;

  while (it <= 2) {
    copy = solution;

    if (it == 1) {
      improved = localSearch->swap1(copy, iteration);
      t2 = clock();
      if (improved) {
        copy.setTimeFound(t1, t2);
      }
    } else if (it == 2) {
      improved = localSearch->swap2(copy, iteration);
      t2 = clock();
      if (improved) {
        copy.setTimeFound(t1, t2);
      }
    }

    if (copy.getObjective() <= solution.getObjective()) {
      it++;
    } else {
      solution = copy;
      solution.timeFound = copy.timeFound;
      it = 1;
    }
  }
}

Solution Ils::Construction(RestartSolution *restart) {
  GreedyKInter kInter(input);
  kInter.setRestart(restart);
  return kInter.run();
}

Solution Ils::Construction(double alpha) {
  return grasp_construction(input, alpha);
}

Solution Ils::Construction() { return ExtendedKInter(input).run(); }

Solution Ils::Perturbation(const Solution &solution, double alpha) {
  return perturbReactive(solution, input, alpha);
}
