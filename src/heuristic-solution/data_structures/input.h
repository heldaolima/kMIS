#ifndef __input_h__
#define __input_h__

#include "subset.h" 
#include <string>

using std::string;

class Input
{
  public: 
    int quantityOfSubsets; // |L|
    int quantityOfElements; // |R|
    int k;
    vector<Subset> subsets;

    Input(string);
    void print();
    void sortByOrder();
    void sortByObjective();

  // private:
    static bool sortByOrderFunc(const Subset &, const Subset &);
    static bool sortByObjectiveFunc(const Subset &, const Subset &);
};

#endif
