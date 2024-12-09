#ifndef __ils_h__
#define __ils_h__

#include "../heuristic.h"
#include "../heuristic_factory.h"
#include "local_search.h"
#include "perturb_strategies/perturbation.h"
#include "restart.h"
#include "stop_strategies/stop_strategy.h"
#include <iostream>

class Ils : public Heuristic {
private:
  const Input *input;
  const LocalSearch *localSearch;
  StopStrategy *stopStrategy;
  const Perturbation &perturbation;
  time_t t1;

  Solution Construction(double);
  Solution Construction();
  Solution Construction(RestartSolution *restart);
  /*Solution Perturbation(const Solution &solution, double alpha);*/
  void Vnd(Solution &solution, int iteration, clock_t t1);

public:
  Ils(const Input *input, const LocalSearch *ls, StopStrategy *stopStrategy,
      const class Perturbation &perturbation)
      : input(input), localSearch(ls), stopStrategy(stopStrategy),
        perturbation(perturbation) {};
  ~Ils() {
    delete stopStrategy;
    delete localSearch;
  }

  virtual Solution run() override;
  virtual void print() const override {
    std::cout << "ILS\n";
    std::cout << "stop: ";
    stopStrategy->print();
    localSearch->print();
  }
};

#endif
