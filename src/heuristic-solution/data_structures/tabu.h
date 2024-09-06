#ifndef _tabu_h_
#define _tabu_h_

#include <sys/types.h>
#include <vector>

#define TENURE 5

using std::vector;

class Tabu {
private:
  int tenure;
  vector<int> tabu_list;

public:
  Tabu() {}
  Tabu(int numberOfSubsets);
  bool isTabu(int item, int iteration);
  void setTabu(int item, int iteration);
  void print();
};

extern Tabu tabu;

#endif
