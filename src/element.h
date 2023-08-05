#ifndef KMIS_ELEMENT
#define KMIS_ELEMENT

#include <bitset>
#include <vector>
#include "globals.h"

using std::bitset, std::vector;

class Element {
  public:
    int id, n;
    bitset<nElems> bits;

    Element(int);
    Element(vector<int>);
    bitset<nElems> intersection(bitset<nElems>);
    static bool sortFunc(const Element&, const Element&);
};

#endif