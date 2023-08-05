#include "graph.h"

Graph::Graph(const char *path) {
  std::fstream inputFile(path);
  if (inputFile.is_open()) {
    int numEdges = 0, set = 0, i = 0;

    inputFile >> this->tam_L;
    inputFile >> this->tam_R;
    inputFile >> numEdges;
    this->adjacencyList.resize(tam_L);

    std::cout << this->tam_L << " " << this->tam_R  << "sizeof adjlist " << adjacencyList.size() << "\n";

    for (i = 0; i < numEdges; i++) {
      int vert1 = 0, vert2 = 0;
      this->mainSet.insert(vert1);
      inputFile >> vert1;
      inputFile >> vert2;
      vert1--; vert2--;
      std::cout << "(" << vert1 << ", " << vert2 << ")\n";
      this->adjacencyList[vert1].push_back(vert2);
    }

    std::cout << "\n\n";
    std::cout << this->adjacencyList.size() << "\n";
    for (i = 0; i < this->adjacencyList.size(); i++) {
      std::cout << i << " --> ";
      for (const int v: this->adjacencyList[i]) {
        std::cout << v << " ";
      }
      std::cout << "\n";
    }
  } else {
    std::cerr << "ERROR: could not open file.\n";
    exit(1);
  }
}