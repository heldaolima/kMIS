#ifndef __input_h__
#define __input_h__

#include "subset.h" 
#include "../globals.h"

class Input
{
  private: 
    int quantityOfSubsets; // |L|
    int quantityOfElements; // |R|
    int k;
    vector<Subset> subsets;

  public:
    Input(const char *);
    int getQuantityOfSubsets();
    int getQuantityOfElements();
    vector<Subset> getSubsets();
    int getK();
    void print();
    void sortByOrder();
    void sortByObjective();
    std::bitset<numberOfBits> getSubset(int);

  // private:
    static bool sortByOrderFunc(const Subset &, const Subset &);
    static bool sortByObjectiveFunc(const Subset &, const Subset &);
    
};

#endif
