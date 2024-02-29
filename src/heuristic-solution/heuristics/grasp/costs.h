#ifndef _costs_h_
#define _costs_h_

#include "../../data_structures/solution.h"
#include "../../data_structures/subset.h"
#include "../../dbg.h"
#include <vector>

using std::vector;

#define getInferiorLimit(alpha, c_min, c_max) ((c_min) + (alpha) * ((c_max) - (c_min)))

typedef struct setForCosts {
  int identifier;
  int objective;
} setForCosts;

typedef struct costs {
  int c_max, c_min;
  vector<setForCosts> incremental_cost;

  costs(vector<Subset> subsets) {
    incremental_cost.push_back({ subsets[0].identifier, subsets[0].getNumberOfElements() });

    c_max = incremental_cost[0].objective;
    c_min = incremental_cost[0].objective;

    for (int i = 1; i < subsets.size(); i++) {
      incremental_cost.push_back({ subsets[i].identifier, subsets[i].getNumberOfElements()});

      if (incremental_cost[i].identifier != -1 && incremental_cost[i].objective > c_max)
        c_max = incremental_cost[i].objective;

      if (incremental_cost[i].identifier != -1 && incremental_cost[i].objective < c_min)
        c_min = incremental_cost[i].objective;
    }
  }

  // int getInferiorLimit(double alpha) {
  //   return (int) c_min + alpha * (c_max - c_min);
  // }

  void update(Solution* solution, vector<Subset> sets) {
    int auxIdx = 0;

    for (const Subset subset: sets) {
      if (subset.identifier != -1) {
        int j = subset.identifier;
        if (!solution->isSubsetInSolution[j]) {
          incremental_cost[j].objective = intersection(solution->bits, subset.bits).count();

          if (auxIdx == 0) {
            c_min = incremental_cost[j].objective;
            c_max = incremental_cost[j].objective;
          }
          else {
            if (incremental_cost[j].objective < c_min)
              c_min = incremental_cost[j].objective;

            if (incremental_cost[j].objective > c_max)
              c_max = incremental_cost[j].objective;
          }
          auxIdx++;
        }
      }
    }
  }
} Costs;

#endif
