#ifndef _lrc_h__
#define _lrc_h__

#include "costs.h"
#include <vector>

using std::vector;

class Lrc {
private:
public:
  vector<bool> lrc;
  Lrc(int);
  int set(const Solution &solution, const vector<setForCosts> &incremental_cost,
          int);
  int getIth(int);
};

#endif
