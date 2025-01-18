#include "stop_target.h"
#include "../../dbg.h"
#include <iostream>

void StopByTargetStrategy::init() {
  clock_t t1 = clock();
  this->t1 = t1;
  elapsedTime = 0.0f;
  currentValue = 0;
}

bool StopByTargetStrategy::stopCondition() {
  return target <= currentValue || elapsedTime >= 30;
}

void StopByTargetStrategy::update(int value) { 
  currentValue = value; 
  clock_t t2 = clock();
  elapsedTime = (t2 - t1) / (double)CLOCKS_PER_SEC;
}

void StopByTargetStrategy::print() const {
  std::cout << "StopByTargetStrategy\n";
}
