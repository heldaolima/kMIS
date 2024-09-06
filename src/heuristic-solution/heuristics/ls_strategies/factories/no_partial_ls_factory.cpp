#include "no_partial_ls_factory.h"
#include "../swap1/noPartial.h"
#include "../swap2/noPartialBeforeAndAfter.h"
#include "../swap2/noPartialComplete.h"

LocalSearchStrategy *NoPartialLSFactory::createSwap1() {
  return new LS_Swap1_NoPartial();
}

LocalSearchStrategy *NoPartialLSFactory::createSwap2(Swap2StrategyEnum strategy) {
  switch (strategy) {
  case BEFORE_AND_AFTER:
    return new LS_Swap2_NoPartial_BeforeAndAfter();
  case COMPLETE:
    return new LS_Swap2_NoPartial_Complete();
  case RANDOM:
    return NULL;
  }
}
