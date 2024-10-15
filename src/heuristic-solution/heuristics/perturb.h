#ifndef __perturb_h__
#define __perturb_h__

#include "../data_structures/input.h"
#include "../data_structures/solution.h"
#include "../helpers/random_utils.h"

Solution perturbReactive(const Solution &solution, const Input *input,
                         double alpha);

#endif
