#ifndef heuristic_factory_h
#define heuristic_factory_h

#include "data_structures/input.h"
#include "heuristic.h"

enum HeuristicsEnum {
  ILS_TIME,
  ILS_ITERATIONS,
};

class HeuristicFactory {
public:
  static Heuristic *create(Input *input, HeuristicsEnum type);
};

#endif
