#ifndef _restart_h_
#define _restart_h_

#include "../data_structures/solution.h"

class RestartSolution {
private:
  const Input *input;
  vector<int> avaliableSets;
  int numberOfAvailableSets;

public:
  const unsigned int noImprovementsThreshold = 75;
  Solution run(clock_t t1);
  void setSubsetAsUsed(int subset);
  RestartSolution();
  RestartSolution(const Input *input)
      : input(input), numberOfAvailableSets(input->quantityOfSubsets) {
    for (int i = 0; i < input->quantityOfSubsets; i++) {
      avaliableSets.push_back(i);
    }
  };
};

#endif // !_restart_h_
