#include "reactive_acceptance.h"
#include <iostream>

void ReactiveAcceptanceCriteria::accept(Solution &current, Solution &best,
                                        Solution &global, int iteration,
                                        clock_t t1) {
  if (current.getObjective() > best.getObjective()) {
    best = current;
    best.setIterationFoud(iteration);
    if (best.getObjective() > global.getObjective()) {
      global = best;
      global.setIterationFoud(iteration);
      iterationsWithoutImprovement = 0;
    }
  } else {
    iterationsWithoutImprovement++;
  }

  if (iterationsWithoutImprovement > noImprovementsThreshold) {
    best = restart->run(t1);
    localSearch->run(best, iteration, t1);

    if (best.getObjective() > global.getObjective()) {
      global = best;
    }
    iterationsWithoutImprovement = 0;
  }
}

string ReactiveAcceptanceCriteria::toString() {
  return "ReactiveAcceptanceCriteria";
}

void ReactiveAcceptanceCriteria::print() { std::cout << toString() << "\n"; }
