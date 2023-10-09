#include "construction.h"
#include "costs.h"
#include "../../random_utlis.h"
#include "lrc.h"
#include "../../dbg.h"

Solution grasp_construction(Input input, double alpha) {
  log_info("alpha: %lf", alpha);
  int i = 0;
  Costs costs(input.subsets);

  Solution solution(input.quantityOfSubsets);
  Lrc lrc(input.quantityOfSubsets);

  i = 0;
  while (i < input.k) {
    // limite mínimo de valor para que o subconjunto entre na LRC
    int inferiorLimit = costs.getInferiorLimit(alpha);
    int tam_lrc = lrc.set(solution, costs, inferiorLimit);

    log_info("inferiorLimit: %d | tam_lrc: %d", inferiorLimit, tam_lrc);

    int randIdx = randint(tam_lrc);
    int idxSubsetChosenInLRC = lrc.getIth(randIdx);

    log_info("randIdx: %d | idxSubsetChosenInLrc: %d", randIdx, idxSubsetChosenInLRC);

    solution.addSubset(idxSubsetChosenInLRC);
    solution.updateBits(input.subsets[idxSubsetChosenInLRC].bits);

    log_info("size of solution: %zu", solution.subsetsInSolution.size());

    if (i + 1 == input.k) break;

    costs.update(solution, input.subsets);

    log_info("construction while %d", i);
    i++;
  }
  return solution;
}

