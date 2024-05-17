#ifndef __greedy_extended_kinter_h__
#define __greedy_extended_kinter_h__

#include "../../heuristic.h"

class ExtendedKInter: Heuristic {
private:
  Input* input;
  clock_t t1;
public:
  ExtendedKInter() {};
  ExtendedKInter(Input* input): input(input) {};
  void setTime(clock_t t1);
  virtual Solution run() override;
};

#endif
