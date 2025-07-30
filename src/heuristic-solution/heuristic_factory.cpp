#include "heuristic_factory.h"
#include "heuristics/acceptance_criteria_strategies/acceptance_criteria_strategy.h"
#include "heuristics/acceptance_criteria_strategies/factory.h"
#include "heuristics/ils.h"
#include "heuristics/local_search.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"
#include "heuristics/ls_strategies/factories/no_partial_ls_factory.h"
#include "heuristics/ls_strategies/factories/use_partial_ls_factory.h"
#include "heuristics/ls_strategies/ls_strategy.h"
#include "heuristics/perturb_strategies/factories/perturbation_factory.h"
#include "heuristics/perturb_strategies/factories/simple_perturbation_factory.h"
#include "heuristics/perturb_strategies/factories/reactive_perturbation_factory.h"
#include "heuristics/perturb_strategies/get_number_strategies/get_number_to_remove_strategy.h"
#include "heuristics/stop_strategies/stop_iteration.h"
#include "heuristics/stop_strategies/stop_target.h"
#include "heuristics/stop_strategies/stop_time.h"
#include <ctime>

Heuristic *HeuristicFactory::createIls(
    const Input *input, const LS_StrategyFactory &lsFactory,
    const PerturbationFactory &perturbationFactory,
    const AcceptanceCriteriaFactory &acceptanceFactory) const {

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
  AcceptanceCriteriaStrategy *ac = acceptanceFactory.create(input, ls);
  return new Ils(input, ls, stop, perturbation, ac);
}

void HeuristicFactory::setTarget(int target) { this->target = target; }

// Main ILS: use data structures, only swap1 and simple perturbation
Heuristic *HeuristicFactory::ttt_createILS1(const Input *input) {
  UsePartialLSFactory lsf(SWAP2_DO_NOT_APPLY);
  LocalSearch *ls =
      new LocalSearch(input, lsf.createSwap1(), lsf.createSwap2());
  StopStrategy *stop = new StopByTargetStrategy(target);
  Perturbation *p = SimplePerturbationFactory(FLOOR_ROOT_OF_K).create();
  AcceptanceCriteriaStrategy *ac =
      AcceptanceCriteriaFactory(ACCEPTANCE_SIMPLE).create(input, ls);

  return new Ils(input, ls, stop, p, ac);
}

// ILS without data structures
Heuristic *HeuristicFactory::ttt_createILS2(const Input *input) {
  NoPartialLSFactory lsf(SWAP2_DO_NOT_APPLY);
  LocalSearch *ls =
      new LocalSearch(input, lsf.createSwap1(), lsf.createSwap2());
  StopStrategy *stop = new StopByTargetStrategy(target);
  Perturbation *p = SimplePerturbationFactory(FLOOR_ROOT_OF_K).create();
  AcceptanceCriteriaStrategy *ac =
      AcceptanceCriteriaFactory(ACCEPTANCE_SIMPLE).create(input, ls);

  return new Ils(input, ls, stop, p, ac);
}

// ILS with reactive perturbation
Heuristic *HeuristicFactory::ttt_createILS3(const Input *input) {

  UsePartialLSFactory lsf(SWAP2_DO_NOT_APPLY);
  LocalSearch *ls =
      new LocalSearch(input, lsf.createSwap1(), lsf.createSwap2());
  StopStrategy *stop = new StopByTargetStrategy(target);
  Perturbation *p = ReactivePerturbationFactory(FLOOR_ROOT_OF_K).create();
  AcceptanceCriteriaStrategy *ac =
      AcceptanceCriteriaFactory(ACCEPTANCE_SIMPLE).create(input, ls);

  return new Ils(input, ls, stop, p, ac);
}

// ILS with VND and Complete Swap(2, 2)
Heuristic *HeuristicFactory::ttt_createILS4(const Input *input) {
  UsePartialLSFactory lsf(SWAP2_COMPLETE);
  LocalSearch *ls =
      new LocalSearch(input, lsf.createSwap1(), lsf.createSwap2());
  StopStrategy *stop = new StopByTargetStrategy(target);
  Perturbation *p = SimplePerturbationFactory(FLOOR_ROOT_OF_K).create();
  AcceptanceCriteriaStrategy *ac =
      AcceptanceCriteriaFactory(ACCEPTANCE_SIMPLE).create(input, ls);

  return new Ils(input, ls, stop, p, ac);
}

Heuristic *HeuristicFactory::createWithPerturbStrategy(const Input *input, NumberToRemoveEstrategyEnum strategy) {
  UsePartialLSFactory lsf(SWAP2_DO_NOT_APPLY);
  LocalSearch *ls = 
    new LocalSearch(input, lsf.createSwap1(), lsf.createSwap2());
  StopStrategy *stop = new StopByTime(input->k);
  Perturbation *p = SimplePerturbationFactory(strategy).create();
  AcceptanceCriteriaStrategy *ac =
    AcceptanceCriteriaFactory(ACCEPTANCE_SIMPLE).create(input, ls);

  return new Ils(input, ls, stop, p, ac);
}
