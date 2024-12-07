#ifndef __number_root_h__
#define __number_root_h__

#include "get_number_to_remove_strategy.h"
#include <cmath>

class GetRootOfK : GetNumberToRemoveStrategy {
public:
  int getNumber(int k) const override {
     return std::floor(std::sqrt(k));
  }
};

#endif
