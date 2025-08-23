#ifndef __swap2_do_nothing_h__
#define __swap2_do_nothing_h__

#include "../ls_strategy.h"

class LS_Swap2_DoNotApply : public LocalSearchStrategy {
public:
  virtual bool swap(const Input *input, Solution &solution,
                    int iteration) override;
  virtual void print() const override { std::cout << toString() << "\n"; }
  virtual string toString() const override { return "LS_Swap2_DoNothing"; }
  virtual bool willBeUsed() const override { return false; };
};

#endif
