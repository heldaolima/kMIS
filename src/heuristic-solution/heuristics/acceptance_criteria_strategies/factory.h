#ifndef __accptance_criteria_factory_h__
#define __accptance_criteria_factory_h__

#include "../local_search.h"
#include "acceptance_criteria_strategy.h"

enum AcceptanceTypes {
  ACCEPTANCE_REACTIVE,
  ACCEPTANCE_SIMPLE,
};

class AcceptanceCriteriaFactory {
private:
  AcceptanceTypes type;

public:
  AcceptanceCriteriaFactory() {}
  AcceptanceCriteriaFactory(AcceptanceTypes type) : type(type) {}
  AcceptanceCriteriaStrategy *create(const Input *input,
                                     const LocalSearch *ls) const;
};

#endif
