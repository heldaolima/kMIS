#ifndef __ils_h__
#define __ils_h__

#include "../data_structures/input.h"
#include "../data_structures/solution.h"

class Ils {
  private:
    Input input;
    Solution Construction(double);
    Solution Construction();
    Solution Perturbation(Solution, double);
    void LocalSearch(Solution&);
    Solution PathRelinking(Solution, Solution);
    void updateEliteSolutions(vector<Solution>&, Solution);
    int getWorstSolutionIdx(vector<Solution>);
  public:
    Ils(Input& input) : input(input) {}
    Solution ils();
};

#endif
