#ifndef heuristic_h
#define heuristic_h

#include "data_structures/input.h"
#include "data_structures/solution.h"

class Heuristic {
public:
    virtual ~Heuristic() {}
    virtual Solution run() = 0;
};

#endif // !heuristic_h
