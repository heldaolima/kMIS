#ifndef __swap2_partial_bf_h__
#define __swap2_partial_bf_h__

#include "../ls_strategy.h"

class LS_Swap2_UsePartial_BeforeAndAfter : public LocalSearchStrategy {
private:
  int getIdxBefore(int i, int qtd);
  int getIdxAfter(int i, int qtd);

public:
  LS_Swap2_UsePartial_BeforeAndAfter(){};
  virtual bool swap(const Input *input, Solution &solution,
                    int iteration) override;
  virtual void print() const override {
    std::cout << toString() << "\n";
  }

  virtual string toString() const override {
    return "LS_Swap2_UsePartial_BeforeAndAfter";
  }
};

#endif
