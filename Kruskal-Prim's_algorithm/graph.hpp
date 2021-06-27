#pragma once
#include "node.hpp"
#include <string>

using namespace std;

class Graph {
public:
    string graph_name;
    int size;
    Node * root;
    Node ** pointers_array;
    Graph();
    ~Graph();
    void printGraph();
    int countEdges();
    void kruskal();
    void prim();
};
