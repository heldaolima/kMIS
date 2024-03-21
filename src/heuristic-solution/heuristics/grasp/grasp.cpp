#include "grasp.h"
#include "../../dbg.h"
#include "../../helpers/random_utils.h"
#include "../../globals.h"
#include "../local_search.h"
#include "../path_relinking.h"
#include "construction.h"
#include "construction_arrays.h"
#include <iostream>

#define MAX_ELITE 10

#define getInferiorLimit(alpha, c_min, c_max) ((c_min) + (alpha) * ((c_max) - (c_min)))

void updateEliteSolutions(vector<Solution>&, Solution);

Solution Grasp_PathRelinking::run() {
  constructionArrays arrays;

  int i = 0, idxAlpha = 0;
  double alpha = 0.0;

  vector<Solution> eliteSolutions;
  int chosenEliteSolution = 0;

  Solution bestSolution(input->quantityOfSubsets);

  for (i = 0; i < MAX_ITERATIONS; i++) {
    idxAlpha = arrays.getIdxAlpha();
    alpha = X[idxAlpha];

    Solution currentSolution = grasp_construction(input, alpha);

    LocalSearch ls = LocalSearch(input, i);
    ls.localSearch(currentSolution);

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

Solution Grasp_Reactive::run() {
  constructionArrays arrays;

  int bestFound = 0;
  int uselessRepetition = 0;

  int i = 0;
  int idxAlpha = 0;
  double alpha = 0.0;

  Solution bestSolution(input->quantityOfSubsets);

  vector<Solution> eliteSolutions;
  int chosenEliteSolution = 0;

  for (i = 0; i < MAX_ITERATIONS; i++) {
    idxAlpha = arrays.getIdxAlpha();
    alpha = X[idxAlpha];

    Solution currentSolution = grasp_construction(input, alpha);

    LocalSearch ls = LocalSearch(input, i);
    ls.localSearch(currentSolution);

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
      bestSolution.setIterationFoud(i);
    }

    arrays.numberOfTimesAnXValueWasChosen[idxAlpha]++;
    arrays.score[idxAlpha] += currentSolution.getObjective();

    if (i % TAM_X)
      arrays.updateProbabilities(bestSolution.getObjective());
  }

  return bestSolution;
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
