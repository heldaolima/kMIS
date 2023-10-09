#ifndef __perturb_h__
#define __perturb_h__

#include "../data_structures/solution.h"
#include "../data_structures/input.h"
#include "../random_utlis.h"

Solution perturb(Solution solution, Input input);
Solution perturbReactive(Solution solution, Input input, double alpha);

#endif
