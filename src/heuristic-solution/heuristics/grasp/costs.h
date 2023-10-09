#ifndef _costs_h_
#define _costs_h_

#include "../../data_structures/solution.h"
#include "../../data_structures/subset.h"
#include <vector>

using std::vector;

typedef struct costs {
  int c_max, c_min;
  vector<int> incremental_cost;

  costs(vector<Subset> subsets) {
    incremental_cost.resize(subsets.size());
    incremental_cost[0] = subsets[0].getNumberOfElements();

    c_max = incremental_cost[0];
    c_min = incremental_cost[0];

    for (int i = 1; i < subsets.size(); i++) {
      incremental_cost[i] = subsets[i].getNumberOfElements();

      if (incremental_cost[i] > c_max)
        c_max = incremental_cost[i];

      if (incremental_cost[i] < c_min)
        c_min = incremental_cost[i];
    }
  }

  int getInferiorLimit(double alpha) {
    return (int) c_min + alpha * (c_max - c_min);
  }

  void update(Solution solution, vector<Subset> sets) {
    int auxIdx = 0;

    for (int j = 0; j < sets.size(); j++) {
      if (!solution.isSubsetInSolution[sets[j].identifier]) {
        incremental_cost[j] = intersection(solution.bits, sets[j].bits).count();

        if (auxIdx == 0) {
          c_min = incremental_cost[j];
          c_max = incremental_cost[j];
        }
        else {
          if (incremental_cost[j] < c_min)
            c_min = incremental_cost[j];
          
          if (incremental_cost[j] > c_max)
            c_max = incremental_cost[j];
        }
        auxIdx++;
      }
    }
  }
} Costs;

#endif
