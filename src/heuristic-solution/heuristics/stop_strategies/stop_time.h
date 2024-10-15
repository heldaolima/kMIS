#ifndef __stop_time_h__
#define __stop_time_h__

#include "stop_strategy.h"
#include <ctime>
#include <iostream>

class StopByTime : public StopStrategy {
private:
  clock_t t1;
  double elapsedTime;
  int k;
  void updateElapsed(clock_t t2);

public:
  StopByTime(int _k) : k(_k) { elapsedTime = 0; };
  virtual void init() override;
  virtual bool stopCondition() override;
  virtual void update() override;
  virtual void print() const override { std::cout << "StopByTime\n"; }
};

#endif
