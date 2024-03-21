#ifndef heuristic_factory_h
#define heuristic_factory_h

#include "heuristic.h"
#include "data_structures/input.h"

enum HeuristicsEnum {
    ILS,
    GRASP_PATH_RELINKING,
    GRASP_REACTIVE,
};

class HeuristicFactory {
public:
    static Heuristic* create(Input* input, HeuristicsEnum type);
};

#endif
