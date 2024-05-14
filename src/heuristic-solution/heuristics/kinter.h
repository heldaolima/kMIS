#ifndef __k_inter_h__
#define __k_inter_h__

#include "../heuristic.h"
#include "../heuristic_factory.h"
#include "restart.h"
#include <vector>

using std::vector;

class GreedyKInter : public Heuristic { 
private:
  Input* input;
  RestartSolution* restart = nullptr;
public:
  GreedyKInter(Input* input) : input(input) {}
  void setRestart(RestartSolution* restart);
  virtual Solution run() override;
  virtual Solution run(clock_t t1) override {
    return run();
  }
};

#endif
