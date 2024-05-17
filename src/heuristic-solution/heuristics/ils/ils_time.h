#ifndef __ils_time_h__
#define __ils_time_h__

#include "../../heuristic.h"
#include "../../heuristic_factory.h"
#include "../restart.h"

class IlsTime: public Heuristic {
private:
  Input* input;
  Solution Construction(double);
  Solution Construction();
  Solution Construction(RestartSolution* restart);
  Solution Perturbation(Solution*, double);
  void LocalSearch(Solution&, int iteration, clock_t t1);
public:
  IlsTime(Input* input) : input(input) {};

  virtual Solution run() override;
};

#endif
