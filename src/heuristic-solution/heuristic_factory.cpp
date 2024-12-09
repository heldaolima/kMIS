#include "heuristic_factory.h"
#include "dbg.h"
#include "heuristics/ils.h"
#include "heuristics/local_search.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"
#include "heuristics/ls_strategies/ls_strategy.h"
#include "heuristics/perturb_strategies/get_number_to_remove_strategy.h"
#include "heuristics/perturb_strategies/number_root.h"
#include "heuristics/perturb_strategies/random_proportion.h"
#include "heuristics/stop_strategies/stop_iteration.h"
#include "heuristics/stop_strategies/stop_time.h"
#include <ctime>

Heuristic *
HeuristicFactory::createIls(const Input *input,
                            const LS_StrategyFactory &factory) const {

  debug("will create ILS");
  StopStrategy *stop;
  switch (stopStrategy) {
  case STOP_TIME: {
    stop = new StopByTime(input->k);
    break;
  }
  case STOP_ITERATIONS: {
    stop = new StopByIteration();
    break;
  }
  }

  LocalSearchStrategy *s1 = factory.createSwap1(), *s2 = factory.createSwap2();
  LocalSearch *ls = new LocalSearch(input, s1, s2);
  GetNumberToRemoveStrategy* getNum;
  if (num_remove == ROOT_OF_K) {
    getNum = new GetRootOfK();
  } else if (num_remove == RANDOM_PROPORTION) {
    getNum = new GetRandomProportionOfK();
  }
  Perturbation* perturbation = new Perturbation(getNum);
  return new Ils(input, ls, stop, perturbation);
}
