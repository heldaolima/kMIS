#ifndef __k_inter_h__
#define __k_inter_h__

#include "../../heuristic.h"
#include "../restart.h"
#include <vector>

using std::vector;

class GreedyKInter : public Heuristic {
private:
  const Input *input;
  RestartSolution *restart = nullptr;

public:
  GreedyKInter(const Input *input) : input(input) {}
  void setRestart(RestartSolution *restart);
  virtual Solution run() override;
  virtual void print() const override {}
  virtual string toString() const override;
};

#endif
