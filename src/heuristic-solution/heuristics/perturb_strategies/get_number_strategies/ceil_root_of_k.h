#ifndef __ceil_root_of_k__
#define __ceil_root_of_k__

#include "get_number_to_remove_strategy.h"
#include <iostream>

class CeilRootOfK: public GetNumberToRemoveStrategy {
public:
  virtual int getNumber(int k) const override;
  virtual void print() override {
    std::cout << "CeilRootOfK\n";
  }

};

#endif
