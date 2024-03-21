#ifndef __times_h__
#define __times_h__

#include <ctime>

typedef struct times {
  double current = 0.0, average = 0.0;

  void set(clock_t t1, clock_t t2) {
    current = (t2 - t1) / (double) CLOCKS_PER_SEC;
    average += current;
  }
} Times;

#endif
