#include "no_partial_ls_factory.h"
#include "../swap1/noPartial.h"
#include "../swap2/doNothing.h"
#include "../swap2/noPartialBeforeAndAfter.h"
#include "../swap2/noPartialComplete.h"
#include "local_search_factory.h"

LocalSearchStrategy *NoPartialLSFactory::createSwap1() const {
  return new LS_Swap1_NoPartial();
}

LocalSearchStrategy *NoPartialLSFactory::createSwap2() const {
  switch (swap2Strategy) {
  case SWAP2_BEFORE_AND_AFTER:
    return new LS_Swap2_NoPartial_BeforeAndAfter();
  case SWAP2_COMPLETE:
    return new LS_Swap2_NoPartial_Complete();
  case SWAP2_RANDOM:
    return nullptr;
  case SWAP2_DO_NOT_APPLY:
    return new LS_Swap2_DoNotApply();
  default:
    return nullptr;
  }
}
