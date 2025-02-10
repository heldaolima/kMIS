#include "input.h"
#include "../dbg.h"
#include "../globals.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using std::fstream, std::vector;

Input::Input(const string &path, bool *solvable) {
  int num_instances, set, value;
  fstream inFile(path);
  if (inFile.is_open()) {
    int i = 0, j = 0;
    inFile >> this->quantityOfSubsets >> this->quantityOfElements >>
        num_instances >> this->k;

    int tam_L = this->quantityOfSubsets;
    int tam_R = this->quantityOfElements;

    for (i = 0; i < tam_L; i++)
      this->subsets.push_back(Subset(i));

    // pre-processing
    vector<vector<bool>> A(tam_L, vector<bool>(tam_R, false));
    for (j = 0; j < num_instances; j++) {
      inFile >> set >> value;
      A[set - 1][value - 1] = true;
    }

    int hasSolution = 0, neighborhood = 0;
    vector<bool> inElement(tam_R);
    for (i = 0; i < tam_R; i++) {
      neighborhood = 0;
      for (j = 0; j < tam_L; j++) {
        if (A[j][i])
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
      int qtd = 0;
      for (i = 0; i < tam_R; i++) {
        if (inElement[i] && A[j][i]) {
          subsets[j].bits.set(i);
          qtd++;
        }
      }
      subsets[j].qtd = qtd;
    }

    inFile.close();
    *solvable = hasSolution != 0;
  } else {
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
  return a.qtd > b.qtd;
}

bool Input::sortByOrderFunc(const Subset &a, const Subset &b) {
  return a.identifier < b.identifier;
}
