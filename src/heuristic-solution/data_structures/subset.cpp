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

void Subset::setBit(int i) {
  this->bits.set(i);
}

int Subset::getNumberOfElements() {
  return this->bits.count();
}

int Subset::getNumberOfElements() const {
  return this->bits.count();
}

int Subset::getId() {
  return this->identifier;
}

int Subset::getId() const {
  return this->identifier;
}

bitset<numberOfBits> Subset::getBits() {
  return this->bits;
}

void Subset::calculateAndSetIntersection(bitset<numberOfBits> bits) {
  this->bits = intersection(this->bits, bits);
  this->qtd = this->getNumberOfElements();
}

bool sortByObjectiveFunc(const Subset &a, const Subset &b) {
  return a.getNumberOfElements() > b.getNumberOfElements();
}

bool sortByOrderFunc(const Subset &a, const Subset &b) {
  return a.getId() < b.getId();
}

