#include "ils.h"
#include "greedy.h"
#include "local_search.h"
#include "perturb.h"
#include "path_relinking.h"
#include "../random_utlis.h"
#include "../dbg.h"
#include "grasp/construction.h"
#include "grasp/construction_arrays.h"
#include "grasp/costs.h"

#define MAX_ITERATIONS 5
#define MAX_ELITE 10

void updateEliteSolutions(vector<Solution>&, Solution);
int getWorstSolutionIdx(vector<Solution>);

Solution Ils::ils() {
  vector<Solution> eliteSolutions;
  int chosenEliteSolution = 0;

  constructionArrays auxArrays;
  int idxAlpha = auxArrays.getIdxAlpha();
  double alpha = X[idxAlpha];

  Solution bestSolution = Construction(alpha);
  bestSolution.print();
  LocalSearch(bestSolution);

  eliteSolutions.push_back(bestSolution);

  int iteration = 0;

  while (iteration < MAX_ITERATIONS) {
    log_info("ITERATION %d", iteration);
    log_info("Number of elite solutions: %zu", eliteSolutions.size());
    idxAlpha = auxArrays.getIdxAlpha();
    alpha = X[idxAlpha];

    Solution perturbedSolution = Perturbation(bestSolution, alpha);
    LocalSearch(perturbedSolution);

    if (eliteSolutions.size() < MAX_ELITE) {
      eliteSolutions.push_back(perturbedSolution);
    }
    else {
      updateEliteSolutions(eliteSolutions, bestSolution);
    }

    if (eliteSolutions.size() >= 1) {
      log_info("Got into path relinking.");
      chosenEliteSolution = randint(eliteSolutions.size());
      debug("Solutions going into pathRelinking: ");
      perturbedSolution.print();
      eliteSolutions[chosenEliteSolution].print();
      perturbedSolution = PathRelinking(perturbedSolution, eliteSolutions[chosenEliteSolution]);
    }

    log_info("got out of path relinking");

    if (perturbedSolution.getObjective() > bestSolution.getObjective()) {
      bestSolution = perturbedSolution;
    }

    auxArrays.computeIdxAlpha(idxAlpha, perturbedSolution.getObjective());

    // if (iteration % TAM_X == 0)
      auxArrays.updateProbabilities(perturbedSolution.getObjective());

    iteration++;
  }

  return bestSolution;
}

Solution Ils::Construction(double alpha) {
  return grasp_construction(input, alpha);
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
