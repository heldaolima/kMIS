#include "heuristic_factory.h"
#include "heuristics/ils.h"
#include "heuristics/local_search.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"
#include "heuristics/ls_strategies/ls_strategy.h"
#include "heuristics/stop_strategies/stop_iteration.h"
#include "heuristics/stop_strategies/stop_time.h"
#include <ctime>

Heuristic *
HeuristicFactory::createIls(const Input *input,
                            const LS_StrategyFactory &factory) const {
  StopStrategy *stop;
  switch (stopStrategy) {
  case STOP_TIME: {
    clock_t t1 = clock();
    stop = new StopByTime(input->k, t1);
    break;
  }
  case STOP_ITERATIONS: {
    stop = new StopByIteration();
    break;
  }
  }

  LocalSearchStrategy *s1 = factory.createSwap1(), *s2 = factory.createSwap2();

  LocalSearch ls(input, s1, s2);
  return new Ils(input, ls, stop);
}
