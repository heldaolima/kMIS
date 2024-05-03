#include "lrc.h"
#include "../../dbg.h"

Lrc::Lrc(int size) {
  lrc.resize(size, false);
}

int Lrc::set(Solution* solution, vector<setForCosts>* incremental_cost, int inferiorLimit) {
  int tam_lrc = 0;

  for (int j = 0; j < incremental_cost->size(); j++) {
    if (incremental_cost->at(j).identifier != -1) {
      if (
        !solution->isSubsetInSolution[incremental_cost->at(j).identifier] && 
        incremental_cost->at(j).objective >= inferiorLimit
      ) {
        this->lrc[j] = true;
        tam_lrc++;
      } else {
        this->lrc[j] = false;
      }
    }
  }

  return tam_lrc;
}

int Lrc::getIth(int ithSet) {
  int idx = 0;
  for (int i = 0; i < lrc.size(); i++) {
    if (lrc[i]) {
      if (idx == ithSet) {
        return i;
      }

      idx++;
    }
  }

  return -1;
}
