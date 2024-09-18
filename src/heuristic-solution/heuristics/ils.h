#ifndef __ils_h__
#define __ils_h__

#include "../heuristic.h"
#include "../heuristic_factory.h"
#include "local_search.h"
#include "restart.h"
#include "stop_strategies/stop_strategy.h"

class Ils : public Heuristic {
private:
  const Input *input;
  const LocalSearch localSearch;
  StopStrategy *stopStrategy;
  time_t t1;

  Solution Construction(double);
  Solution Construction();
  Solution Construction(RestartSolution *restart);
  Solution Perturbation(const Solution& solution, double alpha);
  void Vnd(Solution &solution, int iteration, clock_t t1);

public:
  Ils(const Input *input, const LocalSearch &ls, StopStrategy *stopStrategy)
      : input(input), localSearch(ls), stopStrategy(stopStrategy){};
  ~Ils() { delete stopStrategy; }

  virtual Solution run() override;
};

#endif
