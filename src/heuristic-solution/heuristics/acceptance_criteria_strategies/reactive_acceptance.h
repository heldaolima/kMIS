#ifndef __reactive_acceptance_h__
#define __reactive_acceptance_h__

#include "../local_search.h"
#include "../restart.h"
#include "acceptance_criteria_strategy.h"

class ReactiveAcceptanceCriteria : public AcceptanceCriteriaStrategy {
private:
  RestartSolution *restart;
  int iterationsWithoutImprovement = 0;
  const int noImprovementsThreshold = 50;
  const LocalSearch *localSearch;

public:
  ReactiveAcceptanceCriteria(RestartSolution *restart, const LocalSearch *ls)
      : restart(restart), localSearch(ls) {}

  virtual void accept(Solution &current, Solution &best, Solution &globalBest,
                      int iteration, clock_t t1) override;
  virtual string toString() override;
  virtual void print() override;
  ~ReactiveAcceptanceCriteria() {
    delete restart;
  }
};

#endif
