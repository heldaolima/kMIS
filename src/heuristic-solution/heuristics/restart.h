#ifndef _restart_h_
#define _restart_h_

#include "../data_structures/solution.h"

class RestartSolution {
private:
  Input* input;
  vector<bool> wasUsedToStartSolution;

public:
  Solution run();
  void setSubsetAsUsed(int subset);
  bool checkUsed(int s);
  RestartSolution(Input* input) : input(input) {
    wasUsedToStartSolution = vector<bool>(input->quantityOfSubsets, false);
  };
};

#endif // !_restart_h_
