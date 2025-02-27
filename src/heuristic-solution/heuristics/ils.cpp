#include "ils.h"
#include "grasp/construction.h"
#include "greedy/extended_kinter.h"
#include "greedy/kinter.h"
#include "restart.h"
#include <ctime>

Solution Ils::run() {
  clock_t t1 = clock(), t2 = clock();

  RestartSolution restart(input);

  stopStrategy->init();

  ExtendedKInter greedy(input);
  greedy.setTime(t1);
  Solution best = greedy.run();

  localSearch->run(best, 0, t1);
  Solution globalBest = best;
  globalBest.timeFound = best.timeFound;

  restart.setSubsetAsUsed(best.subsetsInSolution[0]);
  int iterationsWithoutImprovement = 0, iteration = 1;

  Solution currentSolution;
  while (!stopStrategy->stopCondition()) {
    currentSolution = perturbation->perturb(best, input);
    localSearch->run(currentSolution, iteration, t1);

    acceptanceCriteria->accept(currentSolution, best, globalBest, iteration,
                               t1);

    perturbation->update(iteration, currentSolution, best);
    stopStrategy->update(best.getObjective());
    iteration++;
  }
  return globalBest;
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

void Ils::print() const {
  stopStrategy->print();
  localSearch->print();
  perturbation->print();
  acceptanceCriteria->print();
}

string Ils::toString() const {
  string out = "ILS_";
  out += localSearch->toString() + "_";
  out += perturbation->toString() + "_";
  out += acceptanceCriteria->toString() + "_";

  return out;
}
