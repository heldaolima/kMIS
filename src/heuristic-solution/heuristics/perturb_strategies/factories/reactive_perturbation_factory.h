#ifndef __reactive_perturbation_factory_h__
#define __reactive_perturbation_factory_h__

#include "perturbation_factory.h"

class ReactivePerturbationFactory : public PerturbationFactory {
  NumberToRemoveEstrategyEnum choice;

public:
  ReactivePerturbationFactory(NumberToRemoveEstrategyEnum choice)
      : choice(choice) {}
  virtual Perturbation *create() const override;
};

#endif
