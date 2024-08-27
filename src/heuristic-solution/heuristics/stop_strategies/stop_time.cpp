#include "stop_time.h"

StopByTime::StopByTime(int k, clock_t t1) {
  this->k = k;
  this->t1 = t1;
}

void StopByTime::updateElapsed(clock_t t2) {
  elapsedTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
}

void StopByTime::init() {
  clock_t t2 = clock();

  updateElapsed(t2);
}

bool StopByTime::stopCondition() { return elapsedTime == (double)k / 10; }

void StopByTime::update() {
  clock_t t2 = clock();

  updateElapsed(t2);
}
