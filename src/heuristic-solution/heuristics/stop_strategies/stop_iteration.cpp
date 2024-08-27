#include "stop_iteration.h"

void StopByIteration::init() { this->iteration = 0; }

bool StopByIteration::stopCondition() {
  return this->iteration == MAX_ITERATIONS;
}

void StopByIteration::update() { iteration++; }
