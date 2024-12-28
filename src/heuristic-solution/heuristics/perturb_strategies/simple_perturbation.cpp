#include "simple_perturbation.h"
#include "../../helpers/random_utils.h"

Solution SimplePerturbation::perturb(const Solution &solution,
                                     const Input *input) {
  Solution perturbed = Solution(input->quantityOfSubsets);

  vector<Subset> setsForInsertion = input->subsets;
  int num_avaliableSetsForInsertion =
      setInitialSubsetsAsUnavaliable(solution, setsForInsertion, input);

  bitset<numberOfBits> intersec;
  intersec.set();
  int num_setsToRemove = std::min(removalNumberStrategy->getNumber(input->k),
                                  input->quantityOfSubsets - input->k);
  int num_avaliableSetsForRemoval = input->k;
  vector<int> setsForRemoval = solution.subsetsInSolution;

  for (int i = 0; i < input->k - num_setsToRemove; i++) {
    int chosenIdx = randint(num_avaliableSetsForRemoval);
    perturbed.addSubset(setsForRemoval[chosenIdx]);
    intersec &= input->subsets[setsForRemoval[chosenIdx]].bits;

    std::swap(setsForRemoval[chosenIdx],
              setsForRemoval[num_avaliableSetsForRemoval - 1]);
    num_avaliableSetsForRemoval--;
  }

  for (int i = perturbed.subsetsInSolution.size(); i < input->k; i++) {
    int chosenIdx = randint(num_avaliableSetsForInsertion);
    perturbed.addSubset(setsForInsertion[chosenIdx].identifier);
    intersec &= setsForInsertion[chosenIdx].bits;

    std::swap(setsForInsertion[chosenIdx],
              setsForInsertion[num_avaliableSetsForInsertion - 1]);
    num_avaliableSetsForInsertion--;
  }

  perturbed.setBitsAndObjective(intersec);
  return perturbed;
}

int SimplePerturbation::setInitialSubsetsAsUnavaliable(
    const Solution &solution, vector<Subset> &setsForInsertion,
    const Input *input) const {
  int numberAvaliable = input->quantityOfSubsets;
  for (int i = 0; i < input->k; i++) {
    std::swap(setsForInsertion[solution.subsetsInSolution[i]],
              setsForInsertion[numberAvaliable - 1]);
    numberAvaliable--;
  }

  return numberAvaliable;
}

void SimplePerturbation::update(int currentIteration,
                                const Solution &currentSolution,
                                const Solution &bestSolution) {}
