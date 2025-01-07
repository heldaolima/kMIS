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

  Vnd(best, 0, t1);
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
    Vnd(currentSolution, iteration, t1);
    /*std::cout << "perturbed solution after vnd:\n";*/
    /*currentSolution.print();*/

    if (currentSolution.getObjective() > best.getObjective()) {
      best = currentSolution;
      best.setIterationFoud(iteration);

      if (best.getObjective() > globalBest.getObjective()) {
        std::cout << "found a globalBest\nnew=\n";
        best.print();
        std::cout << "previous:\n";
        globalBest.print();
        std::cout << "\n\n";
        globalBest = best;
        globalBest.setIterationFoud(iteration);
      }

      iterationsWithoutImprovement = 0;
    } else {
      iterationsWithoutImprovement++;
    }

    if (iterationsWithoutImprovement > restart.noImprovementsThreshold) {
      best = restart.run(t1);

      Vnd(best, iteration, t1);
      if (best.getObjective() > globalBest.getObjective()) {
        std::cout << "found a globalBest\nnew=\n";
        best.print();
        std::cout << "previous:\n";
        globalBest.print();
        std::cout << "\n\n";
        globalBest = best;
        globalBest.setIterationFoud(iteration);
      }
      iterationsWithoutImprovement = 0;
    }

    perturbation->update(iteration, currentSolution, best);
    stopStrategy->update(best.getObjective());
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

void Ils::print() const {
  std::cout << "ILS\n";
  std::cout << "stop: ";
  stopStrategy->print();
  localSearch->print();
  perturbation->print();
}

string Ils::toString() const {
  string out = "ILS_";
  out += localSearch->toString() + "_";
  out += perturbation->toString() + "_";

  return out;
}
