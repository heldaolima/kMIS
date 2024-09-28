#ifndef __swap1_no_partial_h__
#define __swap1_no_partial_h__

#include "../ls_strategy.h"
#include <iostream>

class LS_Swap1_NoPartial : public LocalSearchStrategy {
public:
  LS_Swap1_NoPartial() {
    std::cout << "constructor of LS_Swap1_NoPartial";
  }
  virtual bool swap(const Input *input, Solution &solution,
                    int iteration) override;
  virtual void print() const override {
    std::cout << "LS_Swap1_NoPartial\n";
  }
};

#endif
