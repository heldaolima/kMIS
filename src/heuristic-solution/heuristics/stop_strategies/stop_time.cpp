#include "stop_time.h"

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
