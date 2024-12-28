#include "simple_perturbation_factory.h"
#include "../get_number_strategies/number_root.h"
#include "../get_number_strategies/random_proportion.h"
#include "../simple_perturbation.h"

Perturbation *SimplePerturbationFactory::create() const {
  switch (choice) {
  case ROOT_OF_K:
    return new SimplePerturbation(new GetRootOfK());
  case RANDOM_PROPORTION:
    return new SimplePerturbation(new GetRandomProportionOfK());
  default:
    return nullptr;
  }
}
