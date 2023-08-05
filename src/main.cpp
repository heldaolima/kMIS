#include "graph.h"

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cout << "usage: main.out [filename]\n";
    exit(1);
  }

  Graph graph(argv[1]);

  return 0;
}