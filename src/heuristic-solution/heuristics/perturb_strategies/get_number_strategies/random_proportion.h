#ifndef __number_random_h__
#define __number_random_h__

#include "get_number_to_remove_strategy.h"
#include <iostream>

class GetRandomProportionOfK : public GetNumberToRemoveStrategy {
public:
  virtual int getNumber(int k) const override;
  virtual void print() override {
    std::cout << "GetRandomProportionOfK\n";
  }
};

#endif
