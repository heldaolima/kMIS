#ifndef __use_partial_complete_h__
#define __use_partial_complete_h__

#include "../ls_strategy.h"

class LS_Swap2_UsePartial_Complete : public LocalSearchStrategy {
public:
  LS_Swap2_UsePartial_Complete() {}
  virtual bool swap(Input *input, Solution &solution, int iteration);
};

#endif
