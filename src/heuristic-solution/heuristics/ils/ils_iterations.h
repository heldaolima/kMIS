#ifndef __ils_iterations_h__
#define __ils_iterations_h__

#include "../../heuristic.h"
#include "../../heuristic_factory.h"
#include "../restart.h"

class IlsIterations: public Heuristic {
private:
  time_t t1;
  Input* input;
  Solution Construction(double);
  Solution Construction();
  Solution Construction(RestartSolution* restart);
  Solution Perturbation(Solution*, double);
  void LocalSearch(Solution&, int iteration, clock_t t1);
public:
  IlsIterations(Input* input) : input(input) {};

  virtual Solution run() override;
};

#endif

