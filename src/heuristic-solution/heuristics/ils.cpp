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
#include <iostream>

#define NON_IMPROVEMENTS_THRESHOLD 100

void updateEliteSolutions(vector<Solution>&, Solution);
int getWorstSolutionIdx(vector<Solution>);


Solution Ils::run() {
  constructionArrays auxArrays;
  int idxAlpha = auxArrays.getIdxAlpha();
  double alpha = X[idxAlpha];

  RestartSolution restart(input);

  Solution best = Construction(&restart);
  LocalSearch(best);
  Solution globalBest = best;

  int iteration = 0; 
  int iterationsWithoutImprovement = 0;
  int numberOfImprovements = 0;

  Solution currentSolution;
  while (iteration < MAX_ITERATIONS) {
    std::cout << "iteration: " << iteration << "\n";
    idxAlpha = auxArrays.getIdxAlpha();
    alpha = X[idxAlpha];


    // debug("iteration: %d", iteration);
    // debug("created pertubed solution");
    currentSolution = Perturbation(&best, alpha);
    LocalSearch(currentSolution);
    // debug("searched perturbed solution");

    if (currentSolution.getObjective() > best.getObjective()) {
      std::cout << "\nimprovement: ";
      currentSolution.print();
      best = currentSolution;
      best.setIterationFoud(iteration);

      if (best.getObjective() > globalBest.getObjective()) {
        std::cout << "\n\nupdating global best\n";
        globalBest = best;
      }

      iterationsWithoutImprovement = 0;
      numberOfImprovements++;
    } else {
      iterationsWithoutImprovement++;
    }

    if (iterationsWithoutImprovement > NON_IMPROVEMENTS_THRESHOLD) {
      best = restart.run();
      std::cout << "\n\nrestarted best: ";
      best.print();

      LocalSearch(best);
      std::cout << "\nlocal-searched it: \n";
      best.print();
      if (best.getObjective() > globalBest.getObjective()) {
        globalBest = best;
      }
      iterationsWithoutImprovement = 0;
    }

    auxArrays.computeIdxAlpha(idxAlpha, currentSolution.getObjective());

    if (iteration % TAM_X == 0)
      auxArrays.updateProbabilities(best.getObjective());

    iteration++;
  }

  debug("number of improvements: %d", numberOfImprovements);
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
