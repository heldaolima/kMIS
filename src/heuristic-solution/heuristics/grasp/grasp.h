#ifndef __grasp_h__
#define __grasp_h__

#include "../../helpers/random_utils.h"
#include "../../heuristic.h"
#include "../../heuristic_factory.h"
#include "construction.h"

class Grasp_PathRelinking : public Heuristic {
private:
  const Input *input;

public:
  Grasp_PathRelinking(const Input *input) : input(input) {}
  Solution run() override;
  virtual Solution run(clock_t t1) { return run(); }
};

class Grasp_Reactive : public Heuristic {
private:
  const Input *input;

public:
  Grasp_Reactive(const Input *input) : input(input) {}
  virtual Solution run() override;
  virtual Solution run(clock_t t1) { return run(); }
};

#endif
