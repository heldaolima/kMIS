#include "path_relinking.h"
#include "../globals.h"
#include <vector>
#include <iostream>

#define DEBUG

using std::vector, std::cout;

#define printVec(V) for(auto n: V) std::cout << n << " ";

Solution pathRelinking(Input input, Solution origin, Solution destiny) {
  int bestObjective = 0;

  Solution bestSolution(input.quantityOfSubsets);

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

  #ifdef DEBUG
    cout << "Origin: \n";
    printVec(origin.subsetsInSolution);
    cout << "\nDestiny: \n";
    printVec(destiny.subsetsInSolution);
    cout << "\n\tDiferença simétrica: " << difference << "\n";
  #endif
  
  while (difference > 0) {
    bitset<numberOfBits> intersectionOriginDestiny;
    intersectionOriginDestiny.set();

    vector<int> onlyInOrigin, onlyInDestiny;

    for (int i = 0; i < destiny.subsetsInSolution.size(); i++) {
      int q = destiny.subsetsInSolution[i];
      if (origin.isSubsetInSolution[q] == false) {
        onlyInDestiny.push_back(q);
      }
    }

    for (int i = 0; i < origin.subsetsInSolution.size(); i++) {
      int q = origin.subsetsInSolution[i];
      
      if (destiny.isSubsetInSolution[q] == false) {
        onlyInOrigin.push_back(q);
      }
      else {
        intersectionOriginDestiny = intersection(intersectionOriginDestiny, input.subsets[q].bits);
      }
    }

    #ifdef DEBUG
      cout << "\nOnly in origin: ";
      printVec(onlyInOrigin);
      cout << "\n\nOnly in destiny: ";
      printVec(onlyInDestiny);
      cout << "\nIntersectionOriginDestiny: " << intersectionOriginDestiny.to_string() << "\n";
    #endif

    int bestMovement = -1;
    int outOfOrigin = 0, inOrigin = 0;
    bitset<numberOfBits> movementsBits;

    for (const int outOnlyInOrigin : onlyInOrigin) { // this will get out of origin
      cout << "início do loop o que sai da origem: " << outOnlyInOrigin << "\n";
      bitset<numberOfBits> intersectionWithoutTheOneLeftOut = intersectionOriginDestiny;
      
      for (const int inOnlyInOrigin : onlyInOrigin) {
        if (inOnlyInOrigin != outOnlyInOrigin) {
          intersectionWithoutTheOneLeftOut = intersection(
            intersectionWithoutTheOneLeftOut, input.subsets[inOnlyInOrigin].bits
          );
        }
      }

      #ifdef DEBUG
        cout << "\nintersectionWithoutTheOneLeftOut: " << intersectionWithoutTheOneLeftOut << "\n";
      #endif
      
      // cost of movements foreach element only in destiny
      for (const int inDestiny : onlyInDestiny) {
        bitset<numberOfBits> movement = intersection(intersectionWithoutTheOneLeftOut, input.subsets[inDestiny].bits);
        
        int currBest = movement.count();
        // #ifdef DEBUG
        //   cout << "\n\nMovement: " << movement << "\n";
        // #endif 
        
        if (bestMovement < currBest) {
          bestMovement = currBest;
          outOfOrigin = outOnlyInOrigin;
          inOrigin = inDestiny;
          movementsBits = movement;
          cout << "\n\ntrocando os valores: ";
          cout << "outoforigin: " << outOnlyInOrigin << " inOrigin: " << inOrigin << "\n";
        }
      }

      #ifdef DEBUG
        cout << "\n\nMovement in the end: " << movementsBits << "\n";
        cout << "inOrigin: " << inOrigin << "\n";
        cout << "outOrigin: " << outOfOrigin << "\n";
      #endif
    }



    origin.bits = movementsBits;
    origin.isSubsetInSolution[inOrigin] = true;
    origin.isSubsetInSolution[outOfOrigin] = false;

    for (int i = 0; i < origin.subsetsInSolution.size(); i++) {
      if (origin.subsetsInSolution[i] == outOfOrigin) {
        cout << "mudando subset da origem: " << origin.subsetsInSolution[i] << " por " << outOfOrigin << "\n";
        origin.subsetsInSolution[i] = inOrigin;
        break;
      }
    }

    if (origin.getObjective() > bestObjective) {
      bestSolution = origin;
      bestObjective = bestSolution.getObjective();
    }

    #ifdef DEBUG
      cout << "\n\nEND OF THE LOOP: ";
      cout << "\n\nOrigin: ";
      printVec(origin.subsetsInSolution);
      cout << "\n\nDestiny: ";
      printVec(destiny.subsetsInSolution);
      cout << "\nOnly in origin: ";
      printVec(onlyInOrigin);
      cout << "\n\nOnly in destiny: ";
      printVec(onlyInDestiny);
      cout << "\nIntersectionOriginDestiny: " << intersectionOriginDestiny.to_string() << "\n";
    #endif

    difference = origin.symmetricDifference(destiny);
    #ifdef DEBUG
      cout << "Difference at the end of loop: "<< difference << "\n";
    #endif
  }

  return bestSolution;
}
