#ifndef __stop_iteration_h__
#define __stop_iteration_h__

#include "stop_strategy.h"
#include <iostream>

#define MAX_ITERATIONS 500

class StopByIteration : public StopStrategy {
private:
  int iteration = 0;

public:
  virtual void init() override;
  virtual bool stopCondition() override;
  virtual void update() override;
  virtual void print() const override {
    std::cout << "StopByIteration\n";
  }
};

#endif
