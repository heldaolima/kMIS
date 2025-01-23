#ifndef __ils_h__
#define __ils_h__

#include "../heuristic.h"
#include "../heuristic_factory.h"
#include "acceptance_criteria_strategies/acceptance_criteria_strategy.h"
#include "local_search.h"
#include "perturb_strategies/perturbation.h"
#include "restart.h"
#include "stop_strategies/stop_strategy.h"
#include <iostream>

class Ils : public Heuristic {
private:
  const Input *input;
  const LocalSearch *localSearch;
  Perturbation *perturbation;
  StopStrategy *stopStrategy;
  AcceptanceCriteriaStrategy *acceptanceCriteria;
  time_t t1;

  Solution Construction(double);
  Solution Construction();
  Solution Construction(RestartSolution *restart);

public:
  Ils(const Input *input, const LocalSearch *ls, StopStrategy *stopStrategy,
      Perturbation *perturbation, AcceptanceCriteriaStrategy *ac)
      : input(input), localSearch(ls), stopStrategy(stopStrategy),
        perturbation(perturbation), acceptanceCriteria(ac) {};
  ~Ils() {
    delete stopStrategy;
    delete localSearch;
    delete perturbation;
    delete acceptanceCriteria;
  }

  virtual Solution run() override;
  virtual void print() const override;
  virtual string toString() const override;
};

#endif
