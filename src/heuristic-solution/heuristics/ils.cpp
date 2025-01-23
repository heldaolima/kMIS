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
  /*std::cout << "solution on extendedKInter: \n";*/
  /*best.print();*/

  localSearch->run(best, 0, t1);
  Solution globalBest = best;
  /*std::cout << "solution after vnd: \n";*/
  /*globalBest.print();*/
  globalBest.timeFound = best.timeFound;

  restart.setSubsetAsUsed(best.subsetsInSolution[0]);
  int iterationsWithoutImprovement = 0, iteration = 1;

  Solution currentSolution;
  while (!stopStrategy->stopCondition()) {
    currentSolution = perturbation->perturb(best, input);
    /*std::cout << "\nsolution after perturbation: \n";*/
    /*currentSolution.print();*/
    localSearch->run(currentSolution, iteration, t1);
    /*std::cout << "perturbed solution after vnd:\n";*/
    /*currentSolution.print();*/

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
  std::cout << "ILS\n";
  std::cout << "stop: ";
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
