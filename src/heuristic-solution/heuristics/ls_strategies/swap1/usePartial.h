#ifndef __swap1_partial_h__
#define __swap1_partial_h__

#include "../ls_strategy.h"

class LS_Swap1_UsePartial: public LocalSearchStrategy {
public:
  LS_Swap1_UsePartial() {};
  virtual bool swap(Input* input, Solution& solution, int iteration) override;
};

#endif
