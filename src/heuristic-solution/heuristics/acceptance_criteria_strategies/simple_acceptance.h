#ifndef __simple_acceptance_h__
#define __simple_acceptance_h__

#include "acceptance_criteria_strategy.h"
class SimpleAcceptance : public AcceptanceCriteriaStrategy {
public:
  virtual void accept(Solution &current, Solution &best, Solution &global,
                      int iteration, clock_t t1) override;
  virtual string toString() override;
  virtual void print() override;
};

#endif
