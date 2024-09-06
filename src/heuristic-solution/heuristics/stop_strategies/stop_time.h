#ifndef __stop_time_h__
#define __stop_time_h__

#include "stop_strategy.h"
#include <ctime>

class StopByTime : public StopStrategy {
private:
  clock_t t1;
  double elapsedTime;
  int k;
  void updateElapsed(clock_t t2);

public:
  StopByTime(int k, clock_t t1);
  virtual void init() override;
  virtual bool stopCondition() override;
  virtual void update() override;
};

#endif
