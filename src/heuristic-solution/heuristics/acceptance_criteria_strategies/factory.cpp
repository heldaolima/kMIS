#include "factory.h"
#include "reactive_acceptance.h"
#include "simple_acceptance.h"

AcceptanceCriteriaStrategy *
AcceptanceCriteriaFactory::create(const Input *input,
                                  const LocalSearch *ls) const {
  switch (type) {
  case ACCEPTANCE_REACTIVE:
    return new ReactiveAcceptanceCriteria(new RestartSolution(input), ls);
  case ACCEPTANCE_SIMPLE:
    return new SimpleAcceptance();
  default:
    return nullptr;
  }
}
