#include "stop_time.h"
#include "../../dbg.h"

void StopByTime::updateElapsed(clock_t t2) {
  elapsedTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
}

void StopByTime::init() {
  clock_t t1 = clock();
  this->t1 = t1;
  elapsedTime = 0.0f;
}

bool StopByTime::stopCondition() {
  return elapsedTime >= (double)k / 10;
}

void StopByTime::update(int value) {
  clock_t t2 = clock();

  updateElapsed(t2);
}
