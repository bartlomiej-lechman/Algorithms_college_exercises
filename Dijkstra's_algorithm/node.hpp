#pragma once
#include <vector>

using namespace std;

struct Node {
    int value;
    int number;
    vector<Node *> edges_vector;
    vector<int> labels_vector;
    vector<Node *> parents_vector;
};
