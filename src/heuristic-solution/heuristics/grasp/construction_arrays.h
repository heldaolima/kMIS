#ifndef __construction_arrays_h__
#define __construction_arrays_h__

#include "../../helpers/random_utils.h"

#define TAM_X 11
static const double X[TAM_X] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

struct constructionArrays {
  int numberOfTimesAnXValueWasChosen[TAM_X];
  double probX[TAM_X];
  double avg[TAM_X];
  int score[TAM_X];

  constructionArrays() {
    for (int i = 0; i < TAM_X; i++) {
      numberOfTimesAnXValueWasChosen[i] = 0;
      score[i] = 0.0;
      probX[i] = 1.0 / TAM_X;
      avg[i] = 0.0;
      score[i] = 0;
    }
  }

  int getIdxAlpha() {
    int i = 0;
    double cumulativeProbability[TAM_X];
    cumulativeProbability[0] = probX[0];

    for (i = 1; i < TAM_X; i++) {
      cumulativeProbability[i] = cumulativeProbability[i - 1] + probX[i];
    }

    double x = random_double();

    for (i = 0; i < TAM_X; i++) {
      if (x <= cumulativeProbability[i]) {
        return i;
      }
    }
    return 0;
  }

  void computeIdxAlpha(int idxAlpha, int foundObjective) {
    numberOfTimesAnXValueWasChosen[idxAlpha]++;
    score[idxAlpha] += foundObjective;
  }

  void updateProbabilities(int zStar) {
    int i = 0;
    double Q[TAM_X], sigma = 0.0;

    for (i = 0; i < TAM_X; i++) {
      if (numberOfTimesAnXValueWasChosen[i] == 0) {
        return;
      }

      avg[i] = (double) score[i] / numberOfTimesAnXValueWasChosen[i];
      Q[i] = avg[i] / zStar;

      sigma += Q[i];
    }

    for (i = 0; i < TAM_X; i++) {
      probX[i] = Q[i] / sigma;
    }
  }
};

#endif
