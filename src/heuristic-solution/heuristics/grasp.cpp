#include "grasp.h"
#include "../dbg.h"
#include "../random_utlis.h"
#include "../globals.h"
#include "local_search.h"
#include "path_relinking.h"
#include <iostream>

#define MAX_ELITE 10

#define getInferiorLimit(alpha, c_min, c_max) ((c_min) + (alpha) * ((c_max) - (c_min)))

int getSubsetInLRC(vector<bool>, int);
void updateEliteSolutions(vector<Solution>&, Solution);
Solution construction(Input, double);
void initializeCosts(int[], int&, int&, vector<Subset>);
void updateCosts(Input, int[], int&, int&, Solution);

struct constructionArrays {
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

  int getIdxAlpha() {
    int i = 0;
    double cumulativeProbability[TAM_X];
    cumulativeProbability[0] = this->probX[0];

    for (i = 1; i < TAM_X; i++) {
      cumulativeProbability[i] = cumulativeProbability[i - 1] + this->probX[i];
    }

    double x = random_double();

    for (i = 0; i < TAM_X; i++) {
      if (x <= cumulativeProbability[i]) {
        return i;
      }
    }
    return 0;
  }

  void updateProbabilities(int zStar) {
    int i = 0;
    double Q[TAM_X], sigma = 0.0;

    for (i = 0; i < TAM_X; i++) {
      if (this->numberOfTimesAnXValueWasChosen[i] == 0) {
        return;
      }

      this->avg[i] = this->score[i] / this->numberOfTimesAnXValueWasChosen[i];
      Q[i] = this->avg[i] / zStar;

      sigma += Q[i];
    }

    for (i = 0; i < TAM_X; i++) {
      this->probX[i] = Q[i] / sigma;
    }
  }
};

Solution graspWithPathRelinking(Input input) {
  constructionArrays arrays;

  int i = 0, idxAlpha = 0;
  double alpha = 0.0;

  vector<Solution> eliteSolutions;
  int chosenEliteSolution = 0;

  Solution bestSolution(input.getQuantityOfSubsets());
  
  for (i = 0; i < GRASP_MAX_ITERATIONS; i++) {
    idxAlpha = arrays.getIdxAlpha();
    alpha = X[idxAlpha];

    Solution currentSolution = construction(input, alpha);

    localSearch(input, currentSolution);

    if (eliteSolutions.size() >= 1) {
      chosenEliteSolution = randint(eliteSolutions.size());
      currentSolution = pathRelinking(input, currentSolution, eliteSolutions[chosenEliteSolution]);
    }

    if (eliteSolutions.size() < MAX_ELITE) {
      eliteSolutions.push_back(currentSolution);
    } else {
      updateEliteSolutions(eliteSolutions, currentSolution);
    }

    if (i == 0 || currentSolution.getObjective() > bestSolution.getObjective()) {
      bestSolution = currentSolution;
    }  

    arrays.updateProbabilities(bestSolution.getObjective());
  }

  return bestSolution;
}

Solution reactiveGrasp(Input input) {
  constructionArrays arrays;

  int bestFound = 0;
  int uselessRepetition = 0;

  int i = 0;
  int idxAlpha = 0;
  double alpha = 0.0;

  Solution bestSolution(input.getQuantityOfSubsets());

  vector<Solution> eliteSolutions;
  int chosenEliteSolution = 0;

  for (i = 0; i < GRASP_MAX_ITERATIONS; i++) {
    idxAlpha = arrays.getIdxAlpha();
    alpha = X[idxAlpha];

    Solution currentSolution = construction(input, alpha);

    localSearch(input, currentSolution);

    int countPathRel = 0;
    
    arrays.numberOfTimesAnXValueWasChosen[idxAlpha]++;
    arrays.score[idxAlpha] += currentSolution.getObjective();

    arrays.updateProbabilities(bestSolution.getObjective());
  }

  return bestSolution;
}

Solution construction(Input input, double alpha) {
  vector<Subset> subsets = input.getSubsets();

  int incremental_cost[input.getQuantityOfSubsets()];
  incremental_cost[0] = { subsets[0].getNumberOfElements() };
  
  int c_max = incremental_cost[0], c_min = incremental_cost[0];
  initializeCosts(incremental_cost, c_max, c_min, subsets);


  Solution solution(input.getQuantityOfSubsets());
  vector<bool> lrc(input.getQuantityOfSubsets(), false);

  int i = 0;
  while (i < input.getK()) {

    // limite mínimo de valor para que o subconjunto entre na LRC
    int inferiorLimit = getInferiorLimit(alpha, c_min, c_max); 

    int tam_lrc = 0;
    for (int j = 0; j < input.getQuantityOfSubsets(); j++) {
      if (!solution.isSubsetInSolution[j] && incremental_cost[j] >= inferiorLimit) {
        lrc[j] = true;
        tam_lrc++;
      } else {
        lrc[j] = false;
      }
    }

    int randIdx = randint(tam_lrc);
    int idxSubsetChosenInLRC = getSubsetInLRC(lrc, randIdx);

    solution.addSubset(idxSubsetChosenInLRC);
    solution.setIntersection(subsets[idxSubsetChosenInLRC].getBits());

    if (i + 1 == input.getK()) break;
    
    // update costs
    updateCosts(input, incremental_cost, c_min, c_max, solution);

    i++;
  }
  return solution;
}

void initializeCosts(int incremental_cost[], int& c_min, int& c_max, vector<Subset> subsets) {
  int i = 0, audx;
  for (i = 1; i < subsets.size(); i++) {
    incremental_cost[i] = subsets[i].getNumberOfElements();

    if (incremental_cost[i] > c_max) {
      c_max = incremental_cost[i];
    }

    if (incremental_cost[i] < c_min) {
      c_min = incremental_cost[i];
    }
  }
}

void updateCosts(Input input, int incremental_cost[], int& c_min, int& c_max, Solution solution) {
  int auxIdx = 0;
  for (int j = 0; j < input.getQuantityOfSubsets(); j++) {
    if (!solution.isSubsetInSolution[j]) {
      incremental_cost[j] = solution.intersectionWith(input.getSubset(j)).count();

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

void updateEliteSolutions(vector<Solution>& elite, Solution curr) {
  int worstObjective, worstObjectiveIdx;
  for (int j = 0; j < elite.size(); j++) {
    if (j == 0) {
      worstObjective = elite[j].getObjective();

      worstObjectiveIdx = j;
    }

    if (elite[j].getObjective() < worstObjective) {
      worstObjective = elite[j].getObjective();
      worstObjectiveIdx = j;
    }
  }

  if (worstObjective < curr.getObjective()) {
    elite[worstObjectiveIdx] = curr;
  }
}
