#include "ils.h"
#include "greedy.h"
#include "local_search.h"
#include "perturb.h"
#include "path_relinking.h"
#include "../helpers/random_utils.h"
#include "../dbg.h"
#include "grasp/construction.h"
#include "grasp/construction_arrays.h"
#include "grasp/costs.h"

#define MAX_ITERATIONS 500
#define MAX_ELITE 10

void updateEliteSolutions(vector<Solution>&, Solution);
int getWorstSolutionIdx(vector<Solution>);

Solution Ils::run() {
  vector<Solution> eliteSolutions;
  int chosenEliteSolution = 0;

  constructionArrays auxArrays;
  int idxAlpha = auxArrays.getIdxAlpha();
  double alpha = X[idxAlpha];

  // Solution bestSolution = Construction(alpha);
  Solution bestSolution = Construction();
  LocalSearch(bestSolution);

  eliteSolutions.push_back(bestSolution);

  int iteration = 0;

  while (iteration < MAX_ITERATIONS) {
    idxAlpha = auxArrays.getIdxAlpha();
    alpha = X[idxAlpha];

    Solution perturbedSolution = Perturbation(bestSolution, alpha);
    LocalSearch(perturbedSolution);


    if (eliteSolutions.size() >= 1) {
      chosenEliteSolution = randint(eliteSolutions.size());
      perturbedSolution = PathRelinking(perturbedSolution, eliteSolutions[chosenEliteSolution]);
    }

    if (perturbedSolution.getObjective() > bestSolution.getObjective()) {
      bestSolution = perturbedSolution;
    }

    if (eliteSolutions.size() < MAX_ELITE) 
      eliteSolutions.push_back(bestSolution);
    else 
      updateEliteSolutions(eliteSolutions, bestSolution);

    auxArrays.computeIdxAlpha(idxAlpha, perturbedSolution.getObjective());

    if (iteration % TAM_X == 0)
      auxArrays.updateProbabilities(bestSolution.getObjective());

    iteration++;
  }

  return bestSolution;
}

Solution Ils::Construction(double alpha) {
  return grasp_construction(input, alpha);
}

Solution Ils::Construction() {
  return GreedyKInter(input).run();
}

Solution Ils::Perturbation(Solution solution, double alpha) {
  return perturbReactive(solution, input, alpha);
}

void Ils::LocalSearch(Solution& solution) {
  localSearch(input, solution);
}

Solution Ils::PathRelinking(Solution origin, Solution destiny) {
  Solution solution = pathRelinking(input, origin, destiny);
  return solution;
}

  // remove the worst one
void Ils::updateEliteSolutions(vector<Solution>& elite, Solution curr) {
  int worstIdx = getWorstSolutionIdx(elite);
  int worstObjective = elite[worstIdx].getObjective();

  if (worstObjective < curr.getObjective()) {
    elite[worstIdx] = curr;
  }
}

int Ils::getWorstSolutionIdx(vector<Solution> solutions) {
  int worstObjective = solutions[0].getObjective();
  int worstIdx = 0;

  for (int i = 1; i < solutions.size(); i++) {
    int currentObjective = solutions[i].getObjective();
    if (currentObjective < worstObjective) {
      worstObjective = currentObjective;
      worstIdx = i;
    }
  }

  return worstIdx;
}
