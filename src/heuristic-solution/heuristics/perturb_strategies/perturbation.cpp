#include "perturbation.h"
#include "../../dbg.h"
#include "../../helpers/random_utils.h"

Solution Perturbation::perturb(const Solution &solution,
                               const Input *input) const {
  debug("inside perturbation");
  debug("input->k = %d", input->k);
  Solution perturbed = Solution(input->quantityOfSubsets);

  vector<Subset> setsForInsertion = input->subsets;
  int num_avaliableSetsForInsertion =
      setInitialSubsetsAsUnavaliable(solution, setsForInsertion, input);
  debug("setted as unavaliable");
  debug("num_avaliableSetsForInsertion: %d", num_avaliableSetsForInsertion);

  bitset<numberOfBits> intersec;
  intersec.set();
  const int num_setsToRemove = numberToRemoveGetter->getNumber(input->k);
  debug("number of sets to remove: %d", num_setsToRemove);
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
  debug("removed subsets");

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

int Perturbation::setInitialSubsetsAsUnavaliable(
    const Solution &solution, vector<Subset> &setsForInsertion,
    const Input *input) const {
  int numberAvaliable = input->quantityOfSubsets;
  debug("numberAvalialble initial: %d", numberAvaliable);
  for (int i = 0; i < input->k; i++) {
    debug("removing %d", solution.subsetsInSolution[i]);
    std::swap(setsForInsertion[solution.subsetsInSolution[i]],
              setsForInsertion[numberAvaliable - 1]);
    numberAvaliable--;
  }

  debug("numberAvalialble final: %d", numberAvaliable);
  return numberAvaliable;
}
