#ifndef __extended_kinter_h__
#define __extended_kinter_h__

#include "../heuristic.h"

class ExtendedKInter: Heuristic {
private:
  Input* input;
public:
  ExtendedKInter(Input* input): input(input) {};
  Solution run() override;
};

#endif
