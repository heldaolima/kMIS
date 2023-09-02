#include "grasp.h"
#include "../dbg.h"
#include "../random_utlis.h"
#include "../globals.h"
#include "local_search.h"
#include <iostream>

typedef struct constructionArrays {
  int numberOfTimesAnXValueWasChosen[TAM_X];
  double probX[TAM_X];
  double avg[TAM_X];
  int score[TAM_X];

  constructionArrays() {
    for (int i = 0; i < TAM_X; i++) {
      numberOfTimesAnXValueWasChosen[i] = 0;
      score[i] = 0.0;
      probX[i] = 1.0 / TAM_X;
      avg[i] = 0.0;
      score[i] = 0;
    }
  }
};

int getIdxAlpha(constructionArrays&);
void updateProbabilities(constructionArrays&, int);
int getSubsetInLRC(vector<bool>, int);
Solution construction(Input, double);

Solution grasp(Input input) {
  vector<Solution> eliteSolutions;
  int bestCost = 0;
  int bestSolutionInConstruction = -1;
  
  constructionArrays arrays;

  int i = 0;
  int idxAlpha = 0;
  double alpha = 0.0;

  Solution bestSolution(input.quantityOfSubsets);

  for (i = 0; i < GRASP_MAX_ITERATIONS; i++) {
    idxAlpha = getIdxAlpha(arrays);
    alpha = X[idxAlpha];
    debug("alpha: %lf", alpha);

    Solution currentSolution = construction(input, alpha);
    debug("currentSolution before LS: %d", currentSolution.getObjective());
    localSearch(input, currentSolution);
    debug("currentSolution after LS: %d", currentSolution.getObjective());
    // pathRelinking(currentSolution);


    if (i == 0 || currentSolution.getObjective() > bestSolution.getObjective()) {
      bestSolution = currentSolution;
    }

    // std::cout << "\n\n";
    // std::cout << "Iteration #" << i << "\n";
    // bestSolution.print();

    arrays.numberOfTimesAnXValueWasChosen[idxAlpha]++;
    arrays.score[idxAlpha] += currentSolution.getObjective();

    // if (i % TAM_X == 0) {
    //   updateProbabilities(arrays, currentSolution.getObjective());
    // }
  }
  return bestSolution;
}

int getIdxAlpha(constructionArrays& arrays) {
  int i = 0;
  double cumulativeProbability[TAM_X];
  cumulativeProbability[0] = arrays.probX[0];
  
  for (i = 1; i < TAM_X; i++) {
    cumulativeProbability[i] = cumulativeProbability[i - 1] + arrays.probX[i];
  }

  double x = random_double();

  for (i = 0; i < TAM_X; i++) {
    if (x <= cumulativeProbability[i]) {
      return i;
    }
  }
}

void updateProbabilities(constructionArrays& arrays, int zStar) {
  int i = 0;
  double Q[TAM_X], sigma = 0.0;

  for (i = 0; i < TAM_X; i++) {
    if (arrays.numberOfTimesAnXValueWasChosen[i] == 0) {
      return;
    }

    arrays.avg[i] = arrays.score[i] / arrays.numberOfTimesAnXValueWasChosen[i];
    Q[i] = arrays.avg[i] / zStar;
    
    sigma += Q[i];
  }

  for (i = 0; i < TAM_X; i++) {
    arrays.probX[i] = Q[i] / sigma;
  }

}

Solution construction(Input input, double alpha) {
  int i = 0;
  int incremental_cost[input.quantityOfSubsets] = 
    { input.subsets[0].getNumberOfElements() };
  
  int c_max = incremental_cost[0], c_min = incremental_cost[0];

  Solution solution(input.quantityOfSubsets);

  vector<bool> lrc(input.quantityOfSubsets, false);

  for (i = 1; i < input.quantityOfSubsets; i++) {
    incremental_cost[i] = input.subsets[i].getNumberOfElements();

    if (incremental_cost[i] > c_max) {
      c_max = incremental_cost[i];
    }

    if (incremental_cost[i] < c_min) {
      c_min = incremental_cost[i];
    }
  }

  i = 0;
  while (i < input.k) {

    // limite mínimo de valor para que o subconjunto entre na LRC
    int inferiorLimit = c_min + alpha * (c_max - c_min); 

    int tam_lrc = 0;
    for (int j = 0; j < input.quantityOfSubsets; j++) {
      if (!solution.isSubsetInSolution[j] && incremental_cost[j] >= inferiorLimit) {
        lrc[j] = true;
        tam_lrc++;
      } else {
        lrc[j] = false;
      }
    }

    int randIdx = randint(tam_lrc);
    int idxSubsetChosenInLRC = getSubsetInLRC(lrc, randIdx);

    debug("chosen subset in LRC: %d", idxSubsetChosenInLRC);

    solution.addSubset(idxSubsetChosenInLRC);
    solution.bits = intersection(solution.bits, input.subsets[idxSubsetChosenInLRC].bits);

    if (i + 1 == input.k) break;
    
    // update costs
    int auxIdx = 0;
    for (int j = 0; j < input.quantityOfSubsets; j++) {
      if (!solution.isSubsetInSolution[j]) {
        incremental_cost[j] = intersection(solution.bits, input.subsets[j].bits).count();
      
        if (auxIdx == 0) {
          c_min = incremental_cost[j];
          c_max = incremental_cost[j];
        } else {
          if (incremental_cost[j] < c_min) {
            c_min = incremental_cost[j];
          }
          if (incremental_cost[j] > c_max) {
            c_max = incremental_cost[j];
          }
        }
        auxIdx++;
      }
    }
    i++;
  }
  return solution;
}

int getSubsetInLRC(vector<bool> lrc, int ithSet) {
  int idx = 0;
  for (int i = 0; i < lrc.size(); i++) {
    if (lrc[i]) {
      if (idx == ithSet) 
        return i;
      idx++;
    }
  }

  return -1;
}