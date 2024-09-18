#ifndef __globals_h__
#define __globals_h__

#include <bitset>
#include <iostream>
#include <map>
#include <vector>

using std::bitset, std::map, std::vector;

#define numberOfBits 300

bitset<numberOfBits> intersection(const bitset<numberOfBits> &setA,
                                  const bitset<numberOfBits> &setB);
void printBits(bitset<numberOfBits> &bits);

template <typename T> void printVec(vector<T> v) {
  for (T el : v) {
    std::cout << el << " ";
  }
  std::cout << "\n";
}

#endif
