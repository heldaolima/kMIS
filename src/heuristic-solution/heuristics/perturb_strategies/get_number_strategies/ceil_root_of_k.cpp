#include "ceil_root_of_k.h"
#include <cmath>

int CeilRootOfK::getNumber(int k) const {
  return static_cast<int>(std::ceil(std::sqrt(k)));
}
