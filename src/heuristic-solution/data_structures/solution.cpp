#include "solution.h"
#include <iostream>
#include <sstream>
#include "input.h"

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

void Solution::removeSubset(int idx, int subset) {
  isSubsetInSolution[subset] = false;
  subsetsInSolution.erase(subsetsInSolution.begin() + idx);
}

void Solution::print() {
  cout << "Objective: " << getObjective() << " | Subsets in solution: ";
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

string Solution::toString() {
  std::stringstream ss;
  ss << "Objective: " << getObjective() << "| Iteration " << iterationFound << " | Subsets in solution: ";

  for (const int el : this->subsetsInSolution) {
    ss << el << " ";
  }

  ss << "\nElements in solution: ";
  for (int i = 0; i < numberOfBits; i++) {
    if (this->bits[i]) {
      ss << i << " ";
    }
  }
  ss << "\n";

  return ss.str();
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

  for (const int s: this->subsetsInSolution) {
    this->updateBits(sets[s].bits);
  }

  this->objective = bits.count();
}

void Solution::updateBits(bitset<numberOfBits> bits) {
  this->bits = intersection(this->bits, bits);
}

void Solution::updateBitsAndObjective(bitset<numberOfBits> bits) {
  this->updateBits(bits);
  this->objective = this->bits.count();
}

void Solution::setBits(bitset<numberOfBits> bits) {
  this->bits = bits;
  // this->objective = bits.count();
}

void Solution::setBitsAndObjective(bitset<numberOfBits> bits) {
  this->bits = bits;
  this->objective = bits.count();
}

Solution Solution::copyWithoutSubsets(Input* input, RemoveSubsets remove) {
  Solution solution(input->quantityOfSubsets);
  for (const int subset: this->subsetsInSolution) {
    if (remove != subset) {
      solution.updateBits(input->subsets[subset].bits);
      solution.addSubset(subset);
    }
  }

  solution.objective = solution.bits.count();
  return solution;
}

void Solution::setIterationFoud(int it) { 
  this->iterationFound = it;
}

unsigned int Solution::getIterationFound() {
  return iterationFound;
}

void Solution::swapSets(int idxOut, int in) {
  // printf("Before swap:\n");
  // print();

  int out = subsetsInSolution[idxOut];
  // debug("idxOut=%d out=%d, in=%d ", idxOut, out, in);


  isSubsetInSolution[out] = false;
  isSubsetInSolution[in] = true;
  subsetsInSolution[idxOut] = in;

  // printf("after swap: ");
  // print();
}

void Solution::swap(int idxOut, int in) {
  swapSets(idxOut, in);
}

void Solution::swap(int idxOut, int in, bitset<numberOfBits> *bits, int newObjective) {
  this->bits = *bits;
  objective = newObjective;

  swapSets(idxOut, in);
}

void Solution::setObjective(unsigned int obj) {
  objective = obj;
}
