#ifndef __perturbation_factory_h__
#define __perturbation_factory_h__

#include "../get_number_strategies/get_number_to_remove_strategy.h"
#include "../perturbation.h"

class PerturbationFactory {
public:
  virtual ~PerturbationFactory();
  virtual Perturbation *create() const = 0;
};

#endif
