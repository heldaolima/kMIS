#include "ceil_log.h"
#include <cmath>

int CeilLogOfK::getNumber(int k) const {
  return static_cast<int>(std::ceil(std::log(k)));
}
