#ifndef __ls_factory_h__
#define __ls_factory_h__

#include "../ls_strategy.h"

enum Swap2StrategyEnum {
  SWAP2_BEFORE_AND_AFTER,
  SWAP2_COMPLETE,
  SWAP2_RANDOM,
};

class LS_StrategyFactory {
public:
  virtual ~LS_StrategyFactory() {}
  virtual LocalSearchStrategy *createSwap1() const = 0;
  virtual LocalSearchStrategy *createSwap2() const = 0;
};

#endif
