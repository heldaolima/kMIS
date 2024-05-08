#ifndef __extended_kinter_h__
#define __extended_kinter_h__

#include "../heuristic.h"

class ExtendedKInter: Heuristic {
private:
  Input* input;
public:
  ExtendedKInter() {};
  ExtendedKInter(Input* input): input(input) {};
  virtual Solution run() override;
  virtual Solution run(Solution best) override {
    return run();
  }
};

#endif
