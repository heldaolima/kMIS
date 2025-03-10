#include "simple_acceptance.h"

void SimpleAcceptance::accept(Solution &current, Solution &best,
                              Solution &global, int iteration, clock_t t1) {
  if (current.getObjective() > best.getObjective()) {
    std::cout << "got improved in the main loop:\n";
    current.print();
    best = current;
    best.setIterationFoud(iteration);
    if (best.getObjective() > global.getObjective()) {
      global = best;
    }
  }
}

string SimpleAcceptance::toString() { return "SimpleAcceptance"; }

void SimpleAcceptance::print() { std::cout << toString() << "\n"; }
