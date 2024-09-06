#include "use_partial_ls_factory.h"
#include "../swap1/usePartial.h"
#include "../swap2/usePartialBeforeAndAfter.h"
#include "../swap2/usePartialComplete.h"
#include "local_search_factory.h"

LocalSearchStrategy *UsePartialLSFactory::createSwap1() {
  return new LS_Swap1_UsePartial();
}

LocalSearchStrategy *UsePartialLSFactory::createSwap2(Swap2StrategyEnum strategy) {
  switch (strategy) {
  case BEFORE_AND_AFTER:
    return new LS_Swap2_UsePartial_BeforeAndAfter();
  case COMPLETE:
    return new LS_Swap2_UsePartial_Complete();
  case RANDOM:
    return NULL;
  }
}
