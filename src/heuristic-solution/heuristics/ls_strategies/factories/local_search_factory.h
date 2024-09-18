#ifndef __ls_factory_h__
#define __ls_factory_h__

#include "../ls_strategy.h"

enum Swap2StrategyEnum {
  BEFORE_AND_AFTER,
  COMPLETE,
  RANDOM,
};

class LS_StrategyFactory {
public:
  ~LS_StrategyFactory() {}
  virtual LocalSearchStrategy *createSwap1() const = 0;
  virtual LocalSearchStrategy *createSwap2() const = 0;
};

#endif
