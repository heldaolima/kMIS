#ifndef __stop_target_h__
#define __stop_target_h__

#include "stop_strategy.h"

class StopByTargetStrategy : public StopStrategy {
  const int target;
  int currentValue;

public:
  StopByTargetStrategy(int target) : target(target) {}

  virtual void init() override;
  virtual bool stopCondition() override;
  virtual void update(int value = 0) override;
  virtual void print() const override;
};

#endif
