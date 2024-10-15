#include "stop_iteration.h"
#include "../../dbg.h"

void StopByIteration::init() {
  this->iteration = 0;
}

bool StopByIteration::stopCondition() {
  return this->iteration == maxIterations;
}

void StopByIteration::update() {
  iteration++;
}
