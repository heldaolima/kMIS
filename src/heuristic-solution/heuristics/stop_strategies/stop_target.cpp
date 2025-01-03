#include "stop_target.h"
#include "../../dbg.h"
#include <iostream>

void StopByTargetStrategy::init() {
  currentValue = 0;
  debug("target=%d", target);
}

bool StopByTargetStrategy::stopCondition() { return target <= currentValue; }

void StopByTargetStrategy::update(int value) { currentValue = value; }

void StopByTargetStrategy::print() const {
  std::cout << "StopByTargetStrategy\n";
}
