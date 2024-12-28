#include "perturbation_factory.h"

class SimplePerturbationFactory : public PerturbationFactory {
  NumberToRemoveEstrategyEnum choice;

public:
  SimplePerturbationFactory(NumberToRemoveEstrategyEnum choice)
      : choice(choice) {}
  virtual Perturbation *create() const override;
};
