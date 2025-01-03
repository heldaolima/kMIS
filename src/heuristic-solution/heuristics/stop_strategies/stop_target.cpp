#include "stop_target.h"
#include <iostream>
#include "../../dbg.h"

void StopByTargetStrategy::init() {
  currentValue = 0;
  debug("target=%d", target);
}

bool StopByTargetStrategy::stopCondition() {
  return target <= currentValue;
}

void StopByTargetStrategy::update(int value) {
  debug("update: value %d", value);
  currentValue = value;
}

void StopByTargetStrategy::print() const {
  std::cout << "StopByTargetStrategy\n";
}
