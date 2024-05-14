#ifndef heuristic_h
#define heuristic_h

#include "data_structures/input.h"
#include "data_structures/solution.h"
#include <ctime>

#define MAX_ITERATIONS 500

class Heuristic {
public:
    virtual ~Heuristic() {}
    virtual Solution run() = 0;
    virtual Solution run(clock_t t1) = 0;
};

#endif // !heuristic_h
