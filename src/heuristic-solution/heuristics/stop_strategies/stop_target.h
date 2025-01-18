#ifndef __stop_target_h__
#define __stop_target_h__

#include "stop_strategy.h"
#include <ctime>

class StopByTargetStrategy : public StopStrategy {
  const int target;
  int currentValue;
  double elapsedTime;
  clock_t t1;

public:
  StopByTargetStrategy(int target) : target(target) { elapsedTime = 0; }

  virtual void init() override;
  virtual bool stopCondition() override;
  virtual void update(int value = 0) override;
  virtual void print() const override;
};

#endif
