#ifndef heuristic_factory_h
#define heuristic_factory_h

#include "heuristic.h"
#include "data_structures/input.h"

class HeuristicFactory {
public:
    virtual Heuristic* create(Input input) = 0;
};

#endif
