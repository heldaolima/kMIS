#ifndef KMIS_GRAPH
#define KMIS_GRAPH

#include <vector>
#include <fstream>
#include <iostream>
#include <set>

using std::cin, std::vector, std::set;

class Graph {
  public:
    Graph(const char*);

    int tam_L;   
    int tam_R;
    int k;

    set<int> mainSet;
    vector<vector<int>> adjacencyList;

};

#endif