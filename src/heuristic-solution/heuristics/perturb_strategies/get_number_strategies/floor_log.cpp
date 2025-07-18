
#include "floor_log.h"
#include <cmath>

int FloorLogOfK::getNumber(int k) const {
  return static_cast<int>(std::floor(std::log(k)));
}
