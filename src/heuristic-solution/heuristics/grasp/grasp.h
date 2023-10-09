#ifndef __grasp_h__
#define __grasp_h__

#include "../../data_structures/input.h"
#include "../../data_structures/solution.h"
#include "../../random_utlis.h"
#include "construction.h"

#define GRASP_MAX_ITERATIONS 200

Solution graspWithPathRelinking(Input input);
Solution reactiveGrasp(Input input);

#endif
