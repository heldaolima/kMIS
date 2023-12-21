#include "solution.h"
#include <iostream>
#include "../dbg.h"
#include "input.h"
#include <algorithm>

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

void Solution::addSubsetAndUpdateIntersection(Subset subset) {
  this->subsetsInSolution.push_back(subset.identifier);
  this->isSubsetInSolution[subset.identifier] = true;
  this->updateBits(subset.bits);
  this->objective = bits.count();
}

void Solution::removeSubset(int subset) {
  this->isSubsetInSolution[subset] = false;
  for (int i = 0; i < this->subsetsInSolution.size(); i++) {
    if (this->subsetsInSolution[i] == subset) {
      this->subsetsInSolution.erase(this->subsetsInSolution.begin() + i);
    }
  }
  this->objective = bits.count();
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
  return this->objective;
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

void Solution::updateIntersection(vector<Subset> sets) {
  this->bits.set();

  std::sort(sets.begin(), sets.end(), Input::sortByOrderFunc);

  for (const int s: this->subsetsInSolution) {
    this->updateBits(sets[s].bits);
  }

  this->objective = bits.count();
}

void Solution::updateBits(bitset<numberOfBits> bits) {
  this->bits = intersection(this->bits, bits);
}

void Solution::setBits(bitset<numberOfBits> bits) {
  this->bits = bits;
  this->objective = bits.count();
}
