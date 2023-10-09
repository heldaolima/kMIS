#include "lrc.h"
#include "../../dbg.h"

Lrc::Lrc(int size) {
  lrc.resize(size, false);
}

int Lrc::set(Solution sol, Costs costs, int inferiorLimit) {
  int tam_lrc = 0;

  for (int j = 0; j < costs.incremental_cost.size(); j++) {
    if (!sol.isSubsetInSolution[j] && costs.incremental_cost[j] >= inferiorLimit) {
      lrc[j] = true;
      tam_lrc++;
    } else {
      lrc[j] = false;
    }
  }

  return tam_lrc;
}

int Lrc::getIth(int ith) {
  log_info("procurando o ith: %d", ith);
  int idx = 0;
  for (int i = 0; i < lrc.size(); i++) {
    if (lrc[i]) {
      log_info("verdadeiro: %d", i);
      if (idx == ith)
        return idx;

      idx++;
    }
    log_info("idx no loop: %d", idx);
  }

  return -1;
}
