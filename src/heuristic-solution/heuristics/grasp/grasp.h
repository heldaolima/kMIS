#ifndef __grasp_h__
#define __grasp_h__

#include "../../heuristic.h"
#include "../../heuristic_factory.h"
#include "../../helpers/random_utils.h"
#include "construction.h"

class Grasp_PathRelinking : public Heuristic {
private:
  const Input* input;
public:
  Grasp_PathRelinking(Input* input) : input(input) {}
  Solution run() override;
  virtual Solution run(clock_t t1) {
    return run();
  }
};

class Grasp_Reactive : public Heuristic {
private:
  Input* input;
public:
  Grasp_Reactive(Input* input) : input(input) {}
  virtual Solution run() override;
  virtual Solution run(clock_t t1) {
    return run();
  }
};


#endif
