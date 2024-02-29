#include "ils.h"
#include "vnd.h"
#include "greedy.h"
#include "perturb.h"
#include "path_relinking.h"
#include "../dbg.h"
#include "grasp/construction.h"
#include "grasp/construction_arrays.h"
#include "grasp/costs.h"
#include <iostream>

void updateEliteSolutions(vector<Solution>&, Solution);
int getWorstSolutionIdx(vector<Solution>);

Solution Ils::run() {
  constructionArrays auxArrays;
  int idxAlpha = auxArrays.getIdxAlpha();
  double alpha = X[idxAlpha];

  // Solution bestSolution = Construction(alpha);
  Solution bestSolution = Construction();
  // debug("created best solution");
  LocalSearch(bestSolution);
  // debug("searched best solution");

  int iteration = 0;
  while (iteration < MAX_ITERATIONS) {
    idxAlpha = auxArrays.getIdxAlpha();
    alpha = X[idxAlpha];

    // debug("iteration: %d", iteration);
    Solution perturbedSolution = Perturbation(&bestSolution, alpha);
    // debug("created pertubed solution");
    LocalSearch(perturbedSolution);
    // debug("searched perturbed solution");

    if (perturbedSolution.getObjective() > bestSolution.getObjective()) {
      bestSolution = perturbedSolution;
      bestSolution.setIterationFoud(iteration);
    }

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

Solution Ils::Perturbation(Solution* solution, double alpha) {
  return perturbReactive(*solution, input, alpha);
}

void Ils::LocalSearch(Solution& solution) {
  vnd(input, solution);
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
