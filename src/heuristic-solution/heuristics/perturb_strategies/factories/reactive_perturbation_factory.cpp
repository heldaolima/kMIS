#include "reactive_perturbation_factory.h"
#include "../get_number_strategies/number_root.h"
#include "../get_number_strategies/random_proportion.h"
#include "../reactive_perturbation.h"

Perturbation *ReactivePerturbationFactory::create() const {
  switch (choice) {
  case ROOT_OF_K:
    return new ReactivePerturbation(new GetRootOfK());
  case RANDOM_PROPORTION:
    return new ReactivePerturbation(new GetRandomProportionOfK());
  default:
    return nullptr;
  }
}
