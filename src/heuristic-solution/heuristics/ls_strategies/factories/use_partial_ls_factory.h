#ifndef __use_partial_ls_factory_h__
#define __use_partial_ls_factory_h__

#include "local_search_factory.h"

class UsePartialLSFactory : public LS_StrategyFactory {
private:
  Swap2StrategyEnum swap2Strategy;

public:
  UsePartialLSFactory(Swap2StrategyEnum swap2Strategy) {
    this->swap2Strategy = swap2Strategy;
  }
  virtual LocalSearchStrategy *createSwap1() override;
  virtual LocalSearchStrategy *createSwap2() override;
};

#endif
