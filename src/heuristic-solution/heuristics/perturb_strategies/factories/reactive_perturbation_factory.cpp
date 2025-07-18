#include "reactive_perturbation_factory.h"
#include "../get_number_strategies/number_root.h"
#include "../get_number_strategies/random_proportion.h"
#include "../get_number_strategies/ceil_root_of_k.h"
#include "../get_number_strategies/floor_log.h"
#include "../get_number_strategies/ceil_log.h"
#include "../reactive_perturbation.h"

Perturbation *ReactivePerturbationFactory::create() const {
  switch (choice) {
  case ROOT_OF_K:
    return new ReactivePerturbation(new GetRootOfK());
  case RANDOM_PROPORTION:
    return new ReactivePerturbation(new GetRandomProportionOfK());
  case CEIL_ROOT_OF_K:
    return new ReactivePerturbation(new CeilRootOfK());
  case FLOOR_LOG:
    return new ReactivePerturbation(new FloorLogOfK());
  case CEIL_LOG:
    return new ReactivePerturbation(new CeilLogOfK());
  default:
    return nullptr;
  }
}
