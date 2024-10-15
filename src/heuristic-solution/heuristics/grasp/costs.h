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

  costs(const vector<bool> &isAvaliable, const vector<Subset> &subsets) {
    bool first = true;
    for (int i = 0; i < subsets.size(); i++) {
      if (!isAvaliable.at(i)) {
        incremental_cost.push_back({ -1, 0 });
      } else {

        incremental_cost.push_back({
          subsets[i].identifier,
          subsets[i].getNumberOfElements(),
        });

        if (first) {
          c_max = incremental_cost[i].objective;
          c_min = incremental_cost[i].objective;
          first = false;
        } else {
          if (
            incremental_cost[i].identifier != -1 && 
            incremental_cost[i].objective > c_max
          )
            c_max = incremental_cost[i].objective;

          if (
            incremental_cost[i].identifier != -1 && 
            incremental_cost[i].objective < c_min
          )
            c_min = incremental_cost[i].objective;
        }
      }
    } 
  }

  void update(const vector<bool>& isAvaliable, const vector<Subset>& sets, const Solution& solution) {
    int auxIdx = 0;

    for (int i = 0; i < sets.size(); i++) {
      if (isAvaliable[i]) {
        int j = sets[i].identifier;
        if (!solution.isSubsetInSolution[j]) {
          incremental_cost[j].objective = intersection(solution.bits, sets[i].bits).count();

          if (auxIdx == 0) {
            c_min = incremental_cost[j].objective;
            c_max = incremental_cost[j].objective;
          } else {
            if (incremental_cost[j].objective < c_min) {
              c_min = incremental_cost[j].objective;
            }

            if (incremental_cost[j].objective > c_max) {
              c_max = incremental_cost[j].objective;
            }
          }
          auxIdx++;
        }
      }
    }
  }
} Costs;

#endif
