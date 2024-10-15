#ifndef heuristic_factory_h
#define heuristic_factory_h

#include "data_structures/input.h"
#include "heuristic.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"

enum StopStrategyEnum {
  STOP_TIME,
  STOP_ITERATIONS,
};

class HeuristicFactory {
private:
  StopStrategyEnum stopStrategy;

public:
  HeuristicFactory(StopStrategyEnum stopStrategy)
      : stopStrategy(stopStrategy) {}

  Heuristic *createIls(const Input *input,
                       const LS_StrategyFactory &factory) const;
};

#endif
