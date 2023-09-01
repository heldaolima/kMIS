#ifndef __subset_h__
#define __subset_h__

#include <bitset>
#include <vector>

#define numberOfBits 301

using std::bitset, std::vector;

class Subset {
public:
  int identifier, qtd;
  bitset<numberOfBits> bits;

  Subset(int);
  Subset(vector<int>);
};

bool sortFunc(const Subset &a, const Subset &b);

#endif