#ifndef __floor_log_perturb_h__
#define __floor_log_perturb_h__

#include "get_number_to_remove_strategy.h"
#include <iostream>

class FloorLogOfK : public GetNumberToRemoveStrategy {
public:
  virtual int getNumber(int k) const override;
  virtual void print() override {
    std::cout << "FloorLogOfK\n";
  }
};

#endif
