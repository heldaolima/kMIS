#include <fstream>
#include <iostream>
#include <algorithm>
#include "build_entry.h"

void build_entry(const char* path, int &tam_L, int &tam_R, int &k, vector<Element> &mainSet) {
  int num_instances, set, value;
  std::fstream inFile(path);
  if (inFile.is_open()) {
    int i = 0, j = 0;
    inFile >> tam_L >> tam_R >> num_instances >> k;
    
    for (i = 0; i < tam_L; i++) {
      mainSet.push_back(Element(i));
    }

    // pre-processing
    bool A[tam_L][tam_R];
    for (i = 0; i < tam_L; i++) {
      for (j = 0; j < tam_R; j++) {
        A[i][j] = false;
      }
    }

    for (j = 0; j < num_instances; j++) {
      inFile >> set >> value;
      A[set-1][value-1] = true;
    }

    int hasSolution = 0;
    bool inElement[tam_R];
    for (i = 0; i < tam_R; i++) {
      int neighborhood = 0;
      for (j = 0; j < tam_L; j++) {
        if (A[i][j]) neighborhood++;
      }
      if (neighborhood < k) {
        inElement[i] = false;
      } else {
        inElement[i] = true;
        hasSolution++;
      }
    }
    
    for (j = 0; j < tam_L; j++) {
      Element element = mainSet[j];
      for (i = 0; i < tam_R; i++) {
        if (inElement[i] && A[j][i]) {
          element.bits.set(i);
        }
      }
      mainSet[j] = element;
    }

    // std::sort(mainSet.begin(), mainSet.end(), Element::sortFunc);

    inFile.close();
  } else {
    exit(1);
  }

}