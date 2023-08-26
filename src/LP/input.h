#ifndef __input_h__
#define __input_h__

#include "subset.h" 

class Input
{
  public: 
  int quantityOfSubsets; // |L|
  int quantityOfElements; //|R|
  int k;
  vector<Subset> subsets;

  Input(const char *);
  bool Neighbors(const int, const int);
  bool nonNeighbors(int, int);
};

#endif