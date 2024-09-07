#ifndef heuristic_factory_h
#define heuristic_factory_h

#include "data_structures/input.h"
#include "heuristic.h"
#include "heuristics/ls_strategies/factories/local_search_factory.h"

enum StopStrategyEnum {
  TIME,
  ITERATIONS,
};

class HeuristicFactory {
private:
  Input *input;
  StopStrategyEnum stopStrategy;

public:
  HeuristicFactory(Input *input, StopStrategyEnum stopStrategy) : input(input) {
    this->stopStrategy = stopStrategy;
  }

  Heuristic *createIls(LS_StrategyFactory *factory);
};

#endif
