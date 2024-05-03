#include "tabu.h"
#include <iostream> 
#include "../partialExperiments.h"

Tabu tabu;

Tabu::Tabu(int numberOfSubsets) {
  tabu_list = vector<int>(numberOfSubsets, 0);
#ifdef TEST
  tenure = tabuTenure;
#else
  tenure = TENURE;
#endif
}

void Tabu::setTabu(int item, int iteration) {
  if (iteration > 0 && useTabu) {
    tabu_list[item] = iteration + tenure;
  }
}

bool Tabu::isTabu(int item, int iteration) {
  // if (tabu_list[item] > iteration) {
  //   std::cout << item << " is tabu at it" << iteration << ", will not add\n";
  // }
  // std::cout << "useTabu: " << useTabu << "\n";
  // std::cout << "item: " << item << " tabu=" << tabu_list[item] << " iteration: " << iteration << "\n";
  // std::cout << "is tabu: " << (tabu_list[item] > iteration) << "\n";
    return useTabu ? tabu_list[item] > iteration : false;
}

void Tabu::print() {
  for (int i = 0; i < tabu_list.size(); i++) {
    std::cout << "{ " << i << ": " << tabu_list[i] << " }\n";
  }
}
