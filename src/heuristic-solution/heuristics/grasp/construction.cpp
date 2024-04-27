#include "construction.h"
#include "costs.h"
#include "../../helpers/random_utils.h"
#include "lrc.h"
#include "../../dbg.h"

Solution grasp_construction(Input* input, double alpha) {
  // int i = 0;
  // // Costs costs(input->subsets);
  //
  Solution solution(input->quantityOfSubsets);
  // Lrc lrc(input->quantityOfSubsets);
  //
  // i = 0;
  // while (i < input->k) {
  //   // limite mínimo de valor para que o subconjunto entre na LRC
  //   // int inferiorLimit = getInferiorLimit(alpha, costs.c_min, costs.c_max);
  //   // int tam_lrc = lrc.set(solution, costs.incremental_cost, inferiorLimit);
  //
  //   int randIdx = randint(tam_lrc);
  //   int idxSubsetChosenInLRC = lrc.getIth(randIdx);
  //
  //   solution.addSubsetAndUpdateIntersection(input->subsets[idxSubsetChosenInLRC]);
  //
  //   if (i + 1 == input->k) break;
  //
  //   costs.update(&solution, input->subsets);
  //
  //   i++;
  // }
  return solution;
}

