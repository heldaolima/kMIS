#ifndef __input_h__
#define __input_h__

#include "subset.h"
#include <string>

using std::string;

class Input {
public:
  int quantityOfSubsets;  // |L|
  int quantityOfElements; // |R|
  int k;
  vector<Subset> subsets;

  Input(string path, bool *solvable);
  void print();
  void sortByOrder();
  void sortByObjective();

  static bool sortByOrderFunc(const Subset &, const Subset &);
  static bool sortByObjectiveFunc(const Subset &, const Subset &);
};

#endif
