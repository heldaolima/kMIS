#ifndef __stop_iteration_h__
#define __stop_iteration_h__

#include "stop_strategy.h"
#include <iostream>


class StopByIteration : public StopStrategy {
private:
  const int maxIterations = 500;
  int iteration = 0;

public:
  virtual void init() override;
  virtual bool stopCondition() override;
  virtual void update(int value = 0) override;
  virtual void print() const override {
    std::cout << "StopByIteration\n";
  }
};

#endif
