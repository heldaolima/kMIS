#include "tabu.h"
#include <iostream> 
#include "local_search.h"

Tabu tabu;

Tabu::Tabu(int numberOfSubsets) {
  tabu_list = vector<int>(numberOfSubsets, 0);
  tenure = TENURE;
}

void Tabu::setTabu(int item, int iteration) {
  // std::cout << "setting tabu: item " << item << "\n";
  if (iteration > 0)
    tabu_list[item] = iteration + tenure;
}

bool Tabu::isTabu(int item, int iteration) {
  // std::cout << "item: " << item << " tabu=" << tabu_list[item] << " iteration: " << iteration << "\n";
  // std::cout << "is tabu: " << (tabu_list[item] > iteration) << "\n";
  return tabu_list[item] > iteration;
}

void Tabu::print() {
  for (int i = 0; i < tabu_list.size(); i++) {
    std::cout << "{ " << i << ": " << tabu_list[i] << " }\n";
  }
}
