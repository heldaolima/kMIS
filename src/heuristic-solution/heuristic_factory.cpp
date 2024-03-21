#include "heuristic_factory.h"
#include "heuristics/grasp/grasp.h"
#include "heuristics/ils.h"

Heuristic* HeuristicFactory::create(Input *input, HeuristicsEnum type) {
  switch (type) {
    case ILS: return new Ils(input);
    case GRASP_REACTIVE: return new Grasp_Reactive(input);
    case GRASP_PATH_RELINKING: return new Grasp_PathRelinking(input);
  }
}
