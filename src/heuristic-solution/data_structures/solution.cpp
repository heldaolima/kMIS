#include "solution.h"
#include <iostream>

using std::cout;

Solution::Solution(int quantityOfSubsets) {
  this->bits.set();
  this->initializeIsSubsetInSolutionVec(quantityOfSubsets);
}

void Solution::initializeIsSubsetInSolutionVec(int quantityOfSubsets) {
  for (int i = 0; i < quantityOfSubsets; i++) {
    this->isSubsetInSolution.push_back(false);
  }
}

void Solution::clean(int qtdSubsets) {
  this->bits.set();
  this->isSubsetInSolution.clear();
  this->subsetsInSolution.clear();
  this->initializeIsSubsetInSolutionVec(qtdSubsets);
}

void Solution::addSubset(int subset) {
  this->subsetsInSolution.push_back(subset);
  this->isSubsetInSolution[subset] = true;
}

void Solution::print() {
  cout << "Subsets in solution: ";
  for (const int el : this->subsetsInSolution) {
    cout << el << " ";
  }
  cout << "\n";
  cout << "Elements in solution: ";
  for (int i = 0; i < numberOfBits; i++) {
    if (this->bits[i]) {
      cout << i << " ";
    }
  }
  cout << "\n";
}

int Solution::getSubsetInSolution(int i) {
  return (i > 0 && i < subsetsInSolution.size()) ? subsetsInSolution[i] : -1;
}

int Solution::getObjective() {
  return this->bits.count();
}

int Solution::symmetricDifference(Solution sol) {
  int count = 0, k = 0;
  for (int subset: this->subsetsInSolution) {
    k++;
    if (sol.isSubsetInSolution[subset]) {
      count++;
    }
  }

  return (k - count);
}