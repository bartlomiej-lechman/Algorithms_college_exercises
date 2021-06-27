#include "edge.hpp"
#include "graph.hpp"
#include <iostream>


using namespace std;

bool comparator(Edge x1, Edge x2) {
    return (x1.weight < x2.weight);
}

int main()
{
    Graph graph;
    graph.kruskal();
    graph.prim();
    return 0;
}
