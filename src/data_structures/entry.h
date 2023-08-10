#ifndef __entry_h__
#define __entry_h__

#include "subset.h" 

class Entry
{
  public: 
  int quantityOfSubsets; // |L|
  int quantityOfElements; //|R|
  int k;
  vector<Subset> subsets;

  Entry(const char *);
};

#endif