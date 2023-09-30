#ifndef __subset_h__
#define __subset_h__

#include <bitset>
#include <vector>
#include "../globals.h"

using std::bitset, std::vector;

class Subset {
private:
  int identifier, qtd;
  bitset<numberOfBits> bits;

public:
  Subset(int);
  Subset(vector<int>);
  void setBit(int);
  int getBit(int);
  int getNumberOfElements();
  int getNumberOfElements() const;
  int getId();
  int getId() const;
  bitset<numberOfBits> getBits();
  void calculateAndSetIntersection(bitset<numberOfBits>);
};

bool sortFunc(const Subset &a, const Subset &b);

#endif
