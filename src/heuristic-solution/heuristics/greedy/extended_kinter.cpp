#include "extended_kinter.h"
#include "../../dbg.h"
#include "../../globals.h"
#include <algorithm>
#include <iostream>

void ExtendedKInter::setTime(clock_t t1) { this->t1 = t1; }

Solution ExtendedKInter::run() {
  vector<Subset> originalSets = input->subsets, loopSets;
  std::sort(originalSets.begin(), originalSets.end(),
            input->sortByObjectiveFunc);

  bitset<numberOfBits> partialBits, bestBits;

  Solution solution(input->quantityOfSubsets);

  clock_t t2;
  int bestIntersection = 0;
  int currentSet = 0;
  while (bestIntersection < originalSets[currentSet].getNumberOfElements() &&
         currentSet < input->quantityOfSubsets) {
    vector<int> subsetsInSolution;
    loopSets = originalSets;

    // current subset needs to get into the solution first
    std::swap(loopSets[0], loopSets[currentSet]);

    subsetsInSolution.push_back(loopSets[0].identifier);
    partialBits = loopSets[0].bits;

    int currentK = 1;
    int currentCount = 0;
    while (currentK < input->k) {
      for (int i = currentK; i < input->quantityOfSubsets; i++) {
        loopSets[i].setBits(intersection(partialBits, loopSets[i].bits));
      }

      std::sort(loopSets.begin() + currentK, loopSets.end(),
                input->sortByObjectiveFunc);
      subsetsInSolution.push_back(loopSets[currentK].identifier);

      partialBits = loopSets[currentK].bits;
      currentCount = partialBits.count();

      currentK++;
      t2 = clock();
      if (currentCount < bestIntersection)
        break;
    }

    if (currentCount > bestIntersection) {
      t2 = clock();
      bestIntersection = currentCount;
      solution.bits = partialBits;
      solution.setObjective(currentCount);
      solution.subsetsInSolution = subsetsInSolution;

      if (currentCount == input->quantityOfSubsets) {
        // cannot get better than that
        break;
      }
    }

    currentSet++;
  }

  for (int s : solution.subsetsInSolution) {
    solution.isSubsetInSolution[s] = true;
  }

  solution.setTimeFound(t1, t2);

  return solution;
}

string ExtendedKInter::toString() const {
  return "ExtendedKInter";
}

/*Solution ExtendedKInter::run() {*/
/*  vector<Subset> conjuntos, conjuntosPrincipalAux = input->subsets;*/
/*  int metrica = 0; // Limite inferior*/
/*  bitset<numberOfBits> bitset_melhor_solucao;*/
/*  vector<int> melhor_solucao;*/
/*  int t = 0;*/
/*  std::sort(conjuntosPrincipalAux.begin(), conjuntosPrincipalAux.end(),*/
/*            Input::sortByObjectiveFunc);*/
/*  Subset x = conjuntosPrincipalAux[0];*/
/**/
/*  while (metrica < x.bits.count() && t < input->quantityOfSubsets) {*/
/*    vector<int> solucao_parcial;*/
/*    conjuntos = conjuntosPrincipalAux;*/
/*    // Coloca o subconjunto inicial na primeira posição*/
/*    Subset aux = conjuntos[0];*/
/*    conjuntos[0] = conjuntos[t];*/
/*    conjuntos[t] = aux;*/
/**/
/*    Subset e = conjuntos[0];*/
/*    solucao_parcial.push_back(e.identifier);*/
/**/
/*    int kk = 1;*/
/*    while (kk < input->k) {*/
/*      for (int i = kk; i < conjuntos.size(); i++) {*/
/*        Subset aux = conjuntos[i];*/
/*        bitset<numberOfBits> vetor_aux = e.bits & aux.bits;*/
/*        aux.bits = vetor_aux;*/
/*        aux.qtd = vetor_aux.count();*/
/*        conjuntos[i] = aux;*/
/*      }*/
/**/
/*      std::sort(conjuntos.begin() + kk, conjuntos.end(),*/
/*                Input::sortByObjectiveFunc);*/
/*      Subset aux = conjuntos[kk];*/
/*      e.bits = aux.bits;*/
/*      solucao_parcial.push_back(aux.identifier);*/
/*      kk++;*/
/**/
/*      if (e.bits.count() < metrica)*/
/*        break;*/
/*    }*/
/*    if (e.bits.count() > metrica) {*/
/*      metrica = e.bits.count();*/
/*      bitset_melhor_solucao = e.bits;*/
/*      melhor_solucao = solucao_parcial;*/
/*      if (metrica == input->quantityOfElements)*/
/*        break;*/
/*    }*/
/**/
/*    t++;*/
/*    if (t < input->quantityOfSubsets)*/
/*      x = conjuntosPrincipalAux[t];*/
/**/
/*    conjuntos.erase(conjuntos.begin(), conjuntos.end());*/
/*  }*/
/*  conjuntosPrincipalAux.erase(conjuntosPrincipalAux.begin(),*/
/*                              conjuntosPrincipalAux.end());*/
/**/
/*  Solution solucao(input->quantityOfSubsets);*/
/*  solucao.setBitsAndObjective(bitset_melhor_solucao);*/
/*  solucao.subsetsInSolution = melhor_solucao;*/
/*  for (int i = 0; i < melhor_solucao.size(); i++) {*/
/*    solucao.isSubsetInSolution[melhor_solucao[i]] = true;*/
/*  }*/
/**/
/*  return solucao;*/
/*}*/
