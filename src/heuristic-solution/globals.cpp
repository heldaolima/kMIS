#include "globals.h"
#include <iostream>

bitset<numberOfBits> intersection(const bitset<numberOfBits> &setA,
                                  const bitset<numberOfBits> &setB) {
  return setA & setB;
}

void printBits(bitset<numberOfBits> &bits) {
  for (int i = 0; i < numberOfBits; i++) {
    if (bits[i]) {
      std::cout << i << " ";
    }
  }
  std::cout << "\n";
}
