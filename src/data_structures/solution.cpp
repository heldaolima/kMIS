#include "solution.h"

Solution::Solution(int quantityOfSubsets) {
  this->initializeIsSubsetInSolutionVec(quantityOfSubsets);
}

void Solution::initializeIsSubsetInSolutionVec(int quantityOfSubsets) {
  for (int i = 0; i < quantityOfSubsets; i++) {
    this->isSubsetInSolution.push_back(false);
  }
}

void Solution::clean() {
  this->bits.set();
  this->isSubsetInSolution.clear();
  this->subsetsInSolution.clear();
}

void Solution::addSubset(int subset) {
  this->subsetsInSolution.push_back(subset);
  this->isSubsetInSolution[subset] = true;
}