#ifndef _restart_h_
#define _restart_h_

#include "../data_structures/solution.h"

class RestartSolution {
private:
  Input* input;
  vector<int> avaliableSets;
  int numberOfAvailableSets;

public:
  Solution run(clock_t t1);
  void setSubsetAsUsed(int subset);
  RestartSolution(Input* input) : input(input) {
    for (int i = 0; i < input->quantityOfSubsets; i++) {
      avaliableSets.push_back(i);
    }
    numberOfAvailableSets = input->quantityOfSubsets;
  };
};

#endif // !_restart_h_
