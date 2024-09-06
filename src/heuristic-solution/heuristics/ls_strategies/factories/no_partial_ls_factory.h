#ifndef __no_partial_ls_factory_h__
#define __no_partial_ls_factory_h__

#include "local_search_factory.h"

class NoPartialLSFactory : public LS_StrategyFactory {
public:
  virtual LocalSearchStrategy *createSwap1() override;
  virtual LocalSearchStrategy *createSwap2(Swap2StrategyEnum strategy) override;
};

#endif
