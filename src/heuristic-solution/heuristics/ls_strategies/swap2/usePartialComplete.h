#ifndef __use_partial_complete_h__
#define __use_partial_complete_h__

#include "../ls_strategy.h"
#include <iostream>

class LS_Swap2_UsePartial_Complete : public LocalSearchStrategy {
public:
  LS_Swap2_UsePartial_Complete() {}
  virtual bool swap(const Input *input, Solution &solution, int iteration) override;
  virtual void print() const override {
    std::cout << "LS_Swap2_UsePartial_Complete\n";
  }
};

#endif
