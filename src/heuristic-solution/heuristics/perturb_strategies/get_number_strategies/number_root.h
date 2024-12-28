#ifndef __number_root_h__
#define __number_root_h__

#include "get_number_to_remove_strategy.h"
#include <iostream>

class GetRootOfK : public GetNumberToRemoveStrategy {
public:
  virtual int getNumber(int k) const override;
  virtual void print() override {
    std::cout << "GetRootOfK\n";
  }
};

#endif
