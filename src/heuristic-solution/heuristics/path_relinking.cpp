#include "path_relinking.h"
#include "../globals.h"
#include <vector>
#include <iostream>

#define DEBUG

using std::vector; 

#define printVec(V) for(auto n: V) std::cout << n << " ";

Solution pathRelinking(Input* input, Solution origin, Solution destiny) {
  int bestObjective = 0;

  Solution bestSolution(input->quantityOfSubsets);

  if (origin.getObjective() > destiny.getObjective()) {
    bestSolution = origin;
    bestObjective = origin.getObjective();
  } else {
    bestSolution = destiny;
    bestObjective = destiny.getObjective();

    destiny = origin;
    origin = bestSolution;
  }
  
  int difference = origin.symmetricDifference(destiny);

  while (difference > 0) {
    bitset<numberOfBits> intersectionOriginDestiny;
    intersectionOriginDestiny.set();

    vector<int> onlyInOrigin, onlyInDestiny;

    // get elements only in origin
    for (int i = 0; i < destiny.subsetsInSolution.size(); i++) {
      int q = destiny.subsetsInSolution[i];
      if (origin.isSubsetInSolution[q] == false) {
        onlyInDestiny.push_back(q);
      }
    }

    // get elements only in destiny
    for (int i = 0; i < origin.subsetsInSolution.size(); i++) {
      int q = origin.subsetsInSolution[i];
      
      if (destiny.isSubsetInSolution[q] == false) {
        onlyInOrigin.push_back(q);
      }
      else {
        intersectionOriginDestiny = intersection(intersectionOriginDestiny, input->subsets[q].bits);
      }
    }

    int bestMovement = -1;
    int outOfOrigin = 0, inOrigin = 0;
    bitset<numberOfBits> movementsBits;

    for (const int outOnlyInOrigin : onlyInOrigin) { // this will get out of origin
      bitset<numberOfBits> intersectionWithoutTheOneLeftOut = intersectionOriginDestiny;
      
      for (const int inOnlyInOrigin : onlyInOrigin) {
        if (inOnlyInOrigin != outOnlyInOrigin) {
          intersectionWithoutTheOneLeftOut = intersection(
            intersectionWithoutTheOneLeftOut, input->subsets[inOnlyInOrigin].bits
          );
        }
      }

      // cost of movements foreach element only in destiny
      for (const int inDestiny : onlyInDestiny) {
        bitset<numberOfBits> movement = intersection(intersectionWithoutTheOneLeftOut, input->subsets[inDestiny].bits);
        
        int currBest = movement.count();
        
        if (bestMovement < currBest) {
          bestMovement = currBest;
          outOfOrigin = outOnlyInOrigin;
          inOrigin = inDestiny;
          movementsBits = movement;
        }
      }
    }

    // do the switch
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

    difference = origin.symmetricDifference(destiny);
  }

  return bestSolution;
}
