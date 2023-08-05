#include "element.h"

Element::Element(int id) {
  this->id = id;
}

Element::Element(vector<int> array) {
  this->bits.reset();
  this->n = array.size();

  for (const int i : array) {
    bits.set((size_t) i);
  }
}

bitset<nElems> Element::intersection(bitset<nElems> otherBits) {
  return this->bits & otherBits;
}

// sorts subsets by number of elements in descending order (bigger first)
bool Element::sortFunc(const Element& a, const Element& b) {
  return a.bits.count() > b.bits.count();
}