#ifndef __swap2_no_partial_complete_h__
#define __swap2_no_partial_complete_h__

#include "../ls_strategy.h"

class LS_Swap2_NoPartial_Complete : public LocalSearchStrategy {
public:
  LS_Swap2_NoPartial_Complete() {};
  virtual bool swap(const Input *input, Solution &solution,
                    int iteration) override;
  virtual void print() const override { std::cout << toString() << "\n"; }

  virtual string toString() const override {
    return "LS_Swap2_NoPartial_Complete";
  }
};

#endif
