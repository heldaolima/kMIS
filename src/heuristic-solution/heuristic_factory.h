#ifndef heuristic_factory_h
#define heuristic_factory_h

#include "data_structures/input.h"
#include "heuristic.h"
#include "heuristics/acceptance_criteria_strategies/factory.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"
#include "heuristics/perturb_strategies/factories/perturbation_factory.h"
#include "heuristics/perturb_strategies/get_number_strategies/get_number_to_remove_strategy.h"

enum StopStrategyEnum {
  STOP_TIME,
  STOP_ITERATIONS,
  STOP_TARGET,
};

class HeuristicFactory {
private:
  StopStrategyEnum stopStrategy;
  int target = 0;

public:
  HeuristicFactory(StopStrategyEnum stopStrategy)
      : stopStrategy(stopStrategy) {}

  Heuristic *
  createIls(const Input *input, const LS_StrategyFactory &lsFactory,
            const PerturbationFactory &perturbationFactory,
            const AcceptanceCriteriaFactory &acceptanceFactory) const;
  void setTarget(int target);
  Heuristic *ttt_createILS1(const Input *input);
  Heuristic *ttt_createILS2(const Input *input);
  Heuristic *ttt_createILS3(const Input *input);
  Heuristic *ttt_createILS4(const Input *input);
};

#endif
