#include <climits>
#include <iostream>
#include "graph.hpp"
#include "node.hpp"

using namespace std;

int main()
{
    Graph graph;
    int node;
    cout << "Enter a number representing a node you want to start from:" << endl;
    while(!(cin >> node) || node < 0)
    {
        cout << "You must enter a valid number." << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    graph.dijkstra(node);
    return 0;
}
