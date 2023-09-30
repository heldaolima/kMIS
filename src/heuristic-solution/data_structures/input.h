#ifndef __input_h__
#define __input_h__

#include "subset.h" 

class Input
{
  public: 
    int quantityOfSubsets; // |L|
    int quantityOfElements; // |R|
    int k;
    vector<Subset> subsets;

    Input(const char *);
    void print();
    void sortByOrder();
    void sortByObjective();

  // private:
    static bool sortByOrderFunc(const Subset &, const Subset &);
    static bool sortByObjectiveFunc(const Subset &, const Subset &);
};

#endif
