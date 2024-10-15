#ifndef __swap2_no_partial_bf_h__
#define __swap2_no_partial_bf_h__

#include "../ls_strategy.h"

class LS_Swap2_NoPartial_BeforeAndAfter : public LocalSearchStrategy {
private:
  int getIdxBefore(int i, int qtd) { return ((i - 1) + qtd) % qtd; }
  int getIdxAfter(int i, int qtd) { return ((i + 1) + qtd) % qtd; }

public:
  LS_Swap2_NoPartial_BeforeAndAfter(){};
  virtual bool swap(const Input *input, Solution &solution,
                    int iteration) override;
  virtual void print() const override {
    std::cout << "LS_Swap2_NoPartial_BeforeAndAfter\n";
  }
};

#endif
