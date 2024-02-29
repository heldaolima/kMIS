#ifndef __greedy_heuristic_h__
#define __greedy_heuristic_h__

#include "../heuristic.h"
#include "../heuristic_factory.h"
#include <vector>

using std::vector;

class GreedyKInter : public Heuristic { 
private:
  Input* input;
public:
  GreedyKInter(Input* input) : input(input) {}
  virtual Solution run() override;
};

class GreedyKInterFactory : public HeuristicFactory {
public:
  virtual Heuristic* create(Input* input) override {
    return new GreedyKInter(input);
  }
};


#endif
