#include "solution.h"

void Solution::clean() {
  this->bits.set();
  this->isInSolution.clear();
  this->elements.clear();
}

void Solution::setIsInSolution(int tam_L) {
  int i = 0;
  for (i = 0; i < tam_L; i++) 
    this->isInSolution.push_back(false);
}

void Solution::addSubset(int subset) {
  this->elements.push_back(subset);
  this->isInSolution[subset] = true;
}