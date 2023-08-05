#include "graph.h"
#include "build_entry.h"

int main(int argc, char* argv[])
{
  // if (argc < 2) {
  //   std::cout << "usage: main.out [filename]\n";
  //   exit(1);
  // }

  int tam_L, tam_R, k;
  vector<Element> mainSet;
  build_entry("classe_1_40_40.txt", tam_L, tam_R, k, mainSet);
  std::cout << tam_L << " " << tam_R << " " << k << "\n";
  for (const Element el: mainSet) {
    std::cout << el.id << "\n";
    std::cout << el.bits.to_string() << "\n";
    std::cout << el.bits.count() << "\n\n";
  }

  // Graph graph(argv[1]);

  return 0;
}