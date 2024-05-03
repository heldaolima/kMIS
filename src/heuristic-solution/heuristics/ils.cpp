#include "ils.h"
#include "vnd.h"
#include "greedy.h"
#include "perturb.h"
#include "path_relinking.h"
#include "../dbg.h"
#include "grasp/construction.h"
#include "grasp/construction_arrays.h"
#include "grasp/costs.h"
#include "restart.h"
#include "tabu.h"
#include "../data_structures/partialSolution.h"
#include "local_search.h"

#define NON_IMPROVEMENTS_THRESHOLD 75

void updateEliteSolutions(vector<Solution>&, Solution);
int getWorstSolutionIdx(vector<Solution>);

Solution Ils::run() {
  constructionArrays auxArrays;
  int idxAlpha = auxArrays.getIdxAlpha();
  double alpha = X[idxAlpha];

  RestartSolution restart(input);

  Solution best = Construction(&restart);
  LocalSearch(best, 0);
  Solution globalBest = best;

  int iteration = 1; 
  int iterationsWithoutImprovement = 0;

  Solution currentSolution;
  while (iteration <= 500) {
    idxAlpha = auxArrays.getIdxAlpha();
    alpha = X[idxAlpha];

    currentSolution = Perturbation(&best, alpha);
    LocalSearch(currentSolution, iteration);


    if (currentSolution.getObjective() > best.getObjective()) {
      // currentSolution.print();
      best = currentSolution;
      best.setIterationFoud(iteration);

      if (best.getObjective() > globalBest.getObjective()) {
        globalBest = best;
        globalBest.setIterationFoud(iteration);
      }

      iterationsWithoutImprovement = 0;
    } else {
      iterationsWithoutImprovement++;
    }

    if (iterationsWithoutImprovement > NON_IMPROVEMENTS_THRESHOLD) {
      best = restart.run();

      // std::cout << "\n\nrestarted best: ";
      // best.print();

      LocalSearch(best, iteration);
      // std::cout << "\nlocal-searched it: \n";
      // best.print();
      if (best.getObjective() > globalBest.getObjective()) {
        globalBest = best;
        globalBest.setIterationFoud(iteration);
      }
      iterationsWithoutImprovement = 0;
    }

    auxArrays.computeIdxAlpha(idxAlpha, currentSolution.getObjective());

    if (iteration % TAM_X == 0)
      auxArrays.updateProbabilities(best.getObjective());

    iteration++;
    // currentSolution.print();
  }

  return globalBest;
}

Solution Ils::Construction(RestartSolution* restart) {
  GreedyKInter kInter(input);
  kInter.setRestart(restart);
  return kInter.run();
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

void Ils::LocalSearch(Solution& solution, int iteration) {
  vnd(input, solution, iteration);
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
