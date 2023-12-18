#include "subset.h"

Subset::Subset(int identifier) {
  this->identifier = identifier;
}

Subset::Subset(vector<int> array) {
  this->bits.reset();

  for (const int number : array) {
    bits.set((size_t) number);
  }
}

int Subset::getNumberOfElements() {
  return (this->identifier != -1) ? this->qtd : -1;
}

bool sortByObjectiveFunc(const Subset &a, const Subset &b) {
  return a.qtd > b.qtd;
}

bool sortByOrderFunc(const Subset &a, const Subset &b) {
  return a.identifier < b.identifier;
}
