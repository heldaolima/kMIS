#ifndef __times_h__
#define __times_h__

#include <ctime>
#include "../dbg.h"

typedef struct times {
  double current = 0.0, average = 0.0;
  double currentFound = 0.0, avgTimeToFindBest = 0.0;

  void set(clock_t t1, clock_t t2) {
    current = (t2 - t1) / (double) CLOCKS_PER_SEC;
    average += current;
  }

  void setTimeToFindBest(clock_t t1, clock_t t2) {
    currentFound = (t2 - t1) / (double) CLOCKS_PER_SEC;
    avgTimeToFindBest += currentFound;
  }

  void setTimeToFindBest(double t) {
    currentFound = t;
    avgTimeToFindBest += t;
  }

} Times;

#endif
