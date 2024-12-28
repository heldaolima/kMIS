#include "number_root.h"
#include <cmath>

int GetRootOfK::getNumber(int k) const {
  return static_cast<int>(std::floor(std::sqrt(k)));
}
