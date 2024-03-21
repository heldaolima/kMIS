#ifndef __subset_h__
#define __subset_h__

#include <bitset>
#include <vector>
#include "../globals.h"

#define NOT_DEFINED -1

using std::bitset, std::vector;

typedef struct RemoveSubsets {
  int s1 = 0;
  int s2 = NOT_DEFINED;

  bool operator!=(int identifier) {
    if (s2 == NOT_DEFINED) 
      return identifier != s1;
    return identifier != s1 && identifier != s2;
  }
} RemoveSubsets;

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
