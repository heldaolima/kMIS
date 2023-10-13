#include "subset.h"

Subset::Subset(int identifier) {
  this->identifier = identifier;
}

Subset::Subset(vector<int> array) {
  this->bits.reset();
  this->qtd = array.size();

  for (const int number : array) {
    bits.set((size_t) number);
  }
}

int Subset::getNumberOfElements() {
  return (this->identifier != -1) ? this->bits.count() : -1;
}

bool sortByObjectiveFunc(const Subset &a, const Subset &b) {
  return a.bits.count() > b.bits.count();
}

bool sortByOrderFunc(const Subset &a, const Subset &b) {
  return a.identifier < b.identifier;
}
