#ifndef __ils_h__
#define __ils_h__

#include "../heuristic.h"
#include "../heuristic_factory.h"
#include "local_search.h"
#include "restart.h"
#include "stop_strategies/stop_strategy.h"

class Ils : public Heuristic {
private:
  StopStrategy *stopStrategy;
  LocalSearch *localSearch;
  time_t t1;
  Input *input;
  Solution Construction(double);
  Solution Construction();
  Solution Construction(RestartSolution *restart);
  Solution Perturbation(Solution *, double);
  void Vnd(Solution &solution, int iteration, clock_t t1);

public:
  Ils(Input *input, StopStrategy *stopStrategy, LocalSearch *ls)
      : input(input) {
    this->stopStrategy = stopStrategy;
    this->localSearch = ls;
  };

  virtual Solution run() override;
};

#endif
