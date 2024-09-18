#ifndef __swap1_no_partial_h__
#define __swap1_no_partial_h__

#include "../ls_strategy.h"

class LS_Swap1_NoPartial : public LocalSearchStrategy {
public:
  LS_Swap1_NoPartial(){};
  virtual bool swap(const Input *input, Solution &solution,
                    int iteration) override;
};

#endif
