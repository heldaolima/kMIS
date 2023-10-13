#ifndef _lrc_h__
#define _lrc_h__

#include <vector>
#include "costs.h"

using std::vector;

class Lrc {
private:
public:
  vector<bool> lrc;
  Lrc(int);
  int set(Solution, vector<setForCosts>, int);
  int getIth(int);
};

#endif
