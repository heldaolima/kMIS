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
  void LocalSearch(Solution&);
  Solution PathRelinking(Solution, Solution);
  void updateEliteSolutions(vector<Solution>&, Solution);
  int getWorstSolutionIdx(vector<Solution>);
  // void accept(Solution* best, Solution* currentSolution, Solution* globalBest);
public:
  Ils(Input* input) : input(input) {};
  virtual Solution run() override;
};

class IlsFactory : public HeuristicFactory {
public:
  Heuristic* create(Input* input) override {
    return new Ils(input);
  }
};

#endif
