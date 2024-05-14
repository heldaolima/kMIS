#ifndef __ils_h__
#define __ils_h__

#include "../heuristic.h"
#include "../heuristic_factory.h"
#include "restart.h"
#include "extended_kinter.h"

class Ils : public Heuristic {
private:
  Input* input;
  Solution Construction(double);
  Solution Construction();
  Solution Construction(RestartSolution* restart);
  Solution Perturbation(Solution*, double);
  void LocalSearch(Solution&, int iteration, clock_t t1);
  Solution PathRelinking(Solution, Solution);
  void updateEliteSolutions(vector<Solution>&, Solution);
  int getWorstSolutionIdx(vector<Solution>);
public:
  Ils(Input* input) : input(input) {};

  virtual Solution run() override;
  virtual Solution run(clock_t t1) override;
};

#endif
