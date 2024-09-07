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
  virtual ~LS_StrategyFactory() {}
  virtual LocalSearchStrategy *createSwap1() = 0;
  virtual LocalSearchStrategy *createSwap2() = 0;
};

#endif
