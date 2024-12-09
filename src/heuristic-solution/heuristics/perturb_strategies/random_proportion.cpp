#include "random_proportion.h"
#include <cstdlib>

int GetRandomProportionOfK::getNumber(int k) const {
  int percentage = rand() % 50 + 1; // Random percentage between 1 and 50
  return static_cast<int>((k * percentage) / 100);
}
