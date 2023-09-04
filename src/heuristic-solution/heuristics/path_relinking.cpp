#include "path_relinking.h"
#include "../globals.h"
#include <vector>
#include <iostream>

#define DEBUG

using std::vector, std::cout;

#define printVec(V) for(auto n: V) std::cout << n << " ";

Solution pathRelinking(Input input, Solution& origin, Solution destiny) {
  Solution bestSolution = origin;
  int bestObjective = origin.getObjective();

  if (destiny.getObjective() > bestObjective) {
    bestObjective = destiny.getObjective();
    bestSolution = destiny;

    destiny = origin;
    origin = bestSolution;
  }

  int difference = symmetricDifference(origin, destiny);

  #ifdef DEBUG
    cout << "Origin: \n";
    origin.print();
    cout << "\nDestiny: \n";
    destiny.print();
    cout << "\n\tDiferença simétrica: " << difference << "\n";
  #endif
  
  while (difference > 0) {
    bitset<numberOfBits> intersectionOriginDestiny;
    intersectionOriginDestiny.set();

    vector<int> onlyInOrigin, onlyInDestiny;

    for (const int destinySubset : destiny.subsetsInSolution) {
      if (!origin.isSubsetInSolution[destinySubset]) {
        onlyInOrigin.push_back(destinySubset);
      }
    }

    for (const int originSubset : origin.subsetsInSolution) {
      if (!destiny.isSubsetInSolution[originSubset]) {
        onlyInDestiny.push_back(originSubset);
      } else {
        intersectionOriginDestiny = intersection(intersectionOriginDestiny, input.subsets[originSubset].bits);
      }
    }

    #ifdef DEBUG
      cout << "Only in origin: ";
      printVec(onlyInOrigin);
      cout << "\n\nOnly in origin: ";
      printVec(onlyInDestiny);
      cout << "";
    #endif

    int bestMovement = -1;
    int outOfOrigin = 0, inOrigin = 0;
    bitset<numberOfBits> movementsBits;

    for (const int outOnlyInOrigin : onlyInOrigin) { // this will get out of origin
      bitset<numberOfBits> intersectionWithoutTheOneLeftOut = intersectionOriginDestiny;
      
      for (const int inOnlyInOrigin : onlyInOrigin) {
        if (inOnlyInOrigin != outOnlyInOrigin) {
          intersectionWithoutTheOneLeftOut = intersection(
            intersectionWithoutTheOneLeftOut, input.subsets[inOnlyInOrigin].bits
          );
        }
      }

      // cost of movements foreach element only in destiny
      bitset<numberOfBits> movement;
      for (const int inDestiny : onlyInDestiny) {
        movement = intersection(intersectionWithoutTheOneLeftOut, input.subsets[inDestiny].bits);
        int currBest = movement.count();
        
        if (currBest > bestMovement) {
          bestMovement = currBest;
          outOfOrigin = outOnlyInOrigin;
          inOrigin = inDestiny;
          movementsBits = movement;
        }
      }
    }

    origin.bits = movementsBits;
    origin.isSubsetInSolution[inOrigin] = true;
    origin.isSubsetInSolution[outOfOrigin] = false;
    for (int i = 0; i < origin.subsetsInSolution.size(); i++) {
      if (origin.subsetsInSolution[i] == outOfOrigin) {
        origin.subsetsInSolution[i] = inOrigin;
        break;
      }
    }

    if (origin.getObjective() > bestObjective) {
      bestSolution = origin;
      bestObjective = bestSolution.getObjective();
    }
    difference = symmetricDifference(origin, destiny);
  }

  return bestSolution;
}

int symmetricDifference(Solution a, Solution b) {
  int count = 0, k = 0;
  for (int subset: a.subsetsInSolution) {
    k++;
    if (b.isSubsetInSolution[subset]) {
      count++;
    }
  }

  return (k - count);
}