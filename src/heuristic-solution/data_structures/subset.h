#ifndef __subset_h__
#define __subset_h__

#include <bitset>
#include <vector>
#include "../globals.h"

using std::bitset, std::vector;

class Subset {
public:
  int identifier, qtd;
  bitset<numberOfBits> bits;

  Subset(int);
  Subset(vector<int>);
  int getNumberOfElements();
  void setBits(bitset<numberOfBits> bits);
};

bool sortFunc(const Subset &a, const Subset &b);

#endif
