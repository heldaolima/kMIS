#include "globals.h"
#include <iostream>

bitset<numberOfBits> intersection(bitset<numberOfBits>& setA, bitset<numberOfBits>& setB) {
  return setA & setB;
}

void printBits(bitset<numberOfBits>& bits) {
  for (int i = 0; i < numberOfBits; i++) {
    if (bits[i]) {
      std::cout << i << " ";
    }
  }
  std::cout << "\n";
}
