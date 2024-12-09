#ifndef __number_root_h__
#define __number_root_h__

#include "get_number_to_remove_strategy.h"
#include <iostream>

class GetRootOfK : public GetNumberToRemoveStrategy {
public:
  GetRootOfK() {
    std::cout << "ioeweasd\n";
  }
  ~GetRootOfK();
  int getNumber(int k) const override;
};

#endif
