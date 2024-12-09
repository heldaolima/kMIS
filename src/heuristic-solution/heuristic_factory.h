#ifndef heuristic_factory_h
#define heuristic_factory_h

#include "data_structures/input.h"
#include "heuristic.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"
#include "heuristics/perturb_strategies/get_number_to_remove_strategy.h"

enum StopStrategyEnum {
  STOP_TIME,
  STOP_ITERATIONS,
};

class HeuristicFactory {
private:
  StopStrategyEnum stopStrategy;
  GetNumberToRemoveStrategy *getNumber;

public:
  HeuristicFactory(StopStrategyEnum stopStrategy,
                   GetNumberToRemoveStrategy *getNumber)
      : stopStrategy(stopStrategy), getNumber(getNumber) {}

  Heuristic *createIls(const Input *input,
                       const LS_StrategyFactory &factory) const;
  ~HeuristicFactory() { delete getNumber; }
};

#endif
