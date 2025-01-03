#include "heuristic_factory.h"
#include "heuristics/ils.h"
#include "heuristics/local_search.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"
#include "heuristics/ls_strategies/ls_strategy.h"
#include "heuristics/perturb_strategies/factories/perturbation_factory.h"
#include "heuristics/stop_strategies/stop_iteration.h"
#include "heuristics/stop_strategies/stop_target.h"
#include "heuristics/stop_strategies/stop_time.h"
#include <ctime>

Heuristic *HeuristicFactory::createIls(
    const Input *input, const LS_StrategyFactory &lsFactory,
    const PerturbationFactory &perturbationFactory) const {

  StopStrategy *stop;
  switch (stopStrategy) {
  case STOP_TIME:
    stop = new StopByTime(input->k);
    break;
  case STOP_ITERATIONS:
    stop = new StopByIteration();
    break;
  case STOP_TARGET:
    stop = new StopByTargetStrategy(target);
    break;
  default:
    break;
  }

  LocalSearchStrategy *s1 = lsFactory.createSwap1(),
                      *s2 = lsFactory.createSwap2();
  LocalSearch *ls = new LocalSearch(input, s1, s2);

  Perturbation *perturbation = perturbationFactory.create();
  return new Ils(input, ls, stop, perturbation);
}

void HeuristicFactory::setTarget(int target) { this->target = target; }
