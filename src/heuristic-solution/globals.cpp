#include "globals.h"

bitset<numberOfBits> intersection(bitset<numberOfBits> setA, bitset<numberOfBits> setB) {
  return setA & setB;
}