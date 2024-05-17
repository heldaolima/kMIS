#include "heuristic_factory.h"
#include "heuristics/ils/ils_time.h"
#include "heuristics/ils/ils_iterations.h"

Heuristic* HeuristicFactory::create(Input *input, HeuristicsEnum type) {
  switch (type) {
    case ILS_TIME: return new IlsTime(input);
    case ILS_ITERATIONS: return new IlsIterations(input);
    default: return NULL;
  }
}
