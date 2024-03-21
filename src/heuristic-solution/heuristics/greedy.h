#ifndef __greedy_heuristic_h__
#define __greedy_heuristic_h__

#include "../heuristic.h"
#include "../heuristic_factory.h"
#include "restart.h"
#include <vector>

using std::vector;

class GreedyKInter : public Heuristic { 
private:
  Input* input;
  RestartSolution* restart;
public:
  GreedyKInter(Input* input) : input(input) {}
  void setRestart(RestartSolution* restart);
  virtual Solution run() override;
};

#endif
