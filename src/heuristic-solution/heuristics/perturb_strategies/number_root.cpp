#include "number_root.h"
#include <cmath>
#include <iostream>

int GetRootOfK::getNumber(int k) const {
  std::cout << "will get number\n";
  return static_cast<int>(std::floor(std::sqrt(k)));
}
GetRootOfK::~GetRootOfK() {
  std::cout << "foi de base\n";
}
