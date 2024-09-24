#include "use_partial_ls_factory.h"
#include "../swap1/usePartial.h"
#include "../swap2/usePartialBeforeAndAfter.h"
#include "../swap2/usePartialComplete.h"
#include "local_search_factory.h"

LocalSearchStrategy *UsePartialLSFactory::createSwap1() const {
  return new LS_Swap1_UsePartial();
}

LocalSearchStrategy *UsePartialLSFactory::createSwap2() const {
  switch (swap2Strategy) {
  case SWAP2_BEFORE_AND_AFTER:
    return new LS_Swap2_UsePartial_BeforeAndAfter();
  case SWAP2_COMPLETE:
    return new LS_Swap2_UsePartial_Complete();
  case SWAP2_RANDOM:
    return NULL;
  default:
    return NULL;
  }
}
