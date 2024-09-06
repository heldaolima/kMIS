#ifndef __random_utils_h__
#define __random_utils_h__

#include <cstdlib>

#define seed() (srand((unsigned)time(NULL)))
#define randint(n) (rand() % n)
#define randintInterval(a, b) ((a) + randint(b))
#define randBetween(a, b) (((a) + lrand48()) % ((b) - (a) + 1))
#define random_double() (rand() / static_cast<double>(RAND_MAX))

inline double random_double_interval(double min, double max) {
  double range = std::abs(max - min);
  double div = RAND_MAX / range;
  return min + (rand() / div);
}

#endif
