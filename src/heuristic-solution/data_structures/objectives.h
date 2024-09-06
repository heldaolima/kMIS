#ifndef __objectives_h__
#define __objectives_h__

typedef struct objectives {
  int current = 0, best = 0, worst = 0;
  double average = 0.0;
  double averageFound = 0.0;

  void set(int objective, int found, int iteration) {
    current = objective;
    average += objective;
    averageFound += found;

    if (iteration == 0) {
      best = current;
      worst = current;
    } else {
      if (current > best)
        best = current;
      if (current < worst)
        worst = current;
    }
  }

} Objectives;

#endif
