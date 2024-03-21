#ifndef __ils_h__
#define __ils_h__

#include "../heuristic.h"
#include "../heuristic_factory.h"
#include "restart.h"

class Ils : public Heuristic {
private:
  Input* input;
  Solution Construction(double);
  Solution Construction();
  Solution Construction(RestartSolution* restart);
  Solution Perturbation(Solution*, double);
  void LocalSearch(Solution&, int iteration);
  Solution PathRelinking(Solution, Solution);
  void updateEliteSolutions(vector<Solution>&, Solution);
  int getWorstSolutionIdx(vector<Solution>);
public:
  Ils(Input* input) : input(input) {};
  virtual Solution run() override;
};

#endif
