#ifndef __no_partial_ls_factory_h__
#define __no_partial_ls_factory_h__

#include "local_search_factory.h"

class NoPartialLSFactory : public LS_StrategyFactory {
private:
  Swap2StrategyEnum swap2Strategy;

public:
  NoPartialLSFactory(Swap2StrategyEnum swap2Strategy)
      : swap2Strategy(swap2Strategy) {}
  virtual LocalSearchStrategy *createSwap1() const override;
  virtual LocalSearchStrategy *createSwap2() const override;
};

#endif
