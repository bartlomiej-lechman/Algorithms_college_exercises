#pragma once
#include <vector>

using namespace std;

class Node {
public:
    int value;
    int number;
    vector<Node *> edges_vector;
    vector<int> labels_vector;
};
