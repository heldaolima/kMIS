#include "input.h"
#include "../globals.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using std::fstream;

Input::Input(const char *path) {
  int num_instances, set, value;
  fstream inFile(path);
  if (inFile.is_open())
  {
    int i = 0, j = 0;
    inFile >> this->quantityOfSubsets >>
        this->quantityOfElements >>
        num_instances >>
        this->k;

    int tam_L = this->quantityOfSubsets;
    int tam_R = this->quantityOfElements;

    for (i = 0; i < tam_L; i++)
      this->subsets.push_back(Subset(i));

    // pre-processing
    bool A[tam_L][tam_R];
    for (i = 0; i < tam_L; i++)
      for (j = 0; j < tam_R; j++)
        A[i][j] = false;

    for (j = 0; j < num_instances; j++) {
      inFile >> set >> value;
      A[set - 1][value - 1] = true;
    }

    int hasSolution = 0;
    bool inElement[tam_R];
    for (i = 0; i < tam_R; i++) {
      int neighborhood = 0;
      for (j = 0; j < tam_L; j++) {
        if (A[i][j])
          neighborhood++;
      }
      if (neighborhood < k) {
        inElement[i] = false;
      } else {
        inElement[i] = true;
        hasSolution++;
      }
    }

    for (j = 0; j < tam_L; j++) {
      Subset subset = subsets[j];
      for (i = 0; i < tam_R; i++) {
        if (inElement[i] && A[j][i]) {
          subset.bits.set(i);
        }
      }
      subsets[j] = subset;
    }

    this->sortByObjective();
    // std::sort(subsets.begin(), subsets.end(), sortFunc);

    inFile.close();
  }
  else {
    std::cout << "ERROR: Could not read file\n";
    exit(1);
  }
}

void Input::print() {
  std::cout << "Number of subsets: " << this->quantityOfSubsets << "\n";
  std::cout << "Number of elements: " << this->quantityOfElements << "\n";
  std::cout << "k: " << this->k << "\n\n";

  for (int i = 0; i < this->quantityOfSubsets; i++) {
    std::cout << i << ": ";
    for (int j = 0; j < this->subsets[i].bits.size(); j++) {
      if (this->subsets[i].bits[j]) {
        std::cout << j << " ";
      }
    }
    std::cout << "\n";
  }
}

void Input::sortByOrder() {
  sort(this->subsets.begin(), this->subsets.end(), this->sortByOrderFunc);
}

void Input::sortByObjective() {
  sort(this->subsets.begin(), this->subsets.end(), this->sortByObjectiveFunc);
}

bool Input::sortByObjectiveFunc(const Subset &a, const Subset &b) {
  return a.bits.count() > b.bits.count();
}

bool Input::sortByOrderFunc(const Subset &a, const Subset &b) {
  return a.identifier < b.identifier;
}
