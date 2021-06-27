#include "compare.hpp"
#include "edge.hpp"
#include "graph.hpp"
#include "node.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <queue>
#include <sstream>
#include <stack>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std; 

bool comparator(Edge x1, Edge x2);

Graph::Graph(){
    char temp[500], temp2[500];
    ifstream input;
    input.open("graph.txt");
    input >> graph_name;
    input >> size;
    
    if(size > 0)
    {
        pointers_array = new Node*[size];
        input >> temp;
        input >> temp;
        root = new Node();
        root->value = atoi(temp);
        root->number = 0;
        pointers_array[0] = root;
        input >> temp;
        int x, y, i, j, k;
        stringstream ss;
        string list = "";
        while(temp[0] != 'T')
        {
            if(list != "")
            {
                list += " ";
            }
            for(i = 0; temp[i] != '('; ++i)
            {
                temp2[i] = temp[i];
            }
            ++i;
            x = atoi(temp2);
            ss << x;
            list = list + ss.str();
            pointers_array[atoi(temp2)] = new Node();
            pointers_array[atoi(temp2)]->number = atoi(temp2);
            for(int z = 0; z <= 50; ++z)
            {temp2[z] = '\0';}
            for(j = 0; temp[i] != ')'; ++i, ++j)
            {
                temp2[j] = temp[i];
            }
            x = atoi(temp2);
            ss.str("");
            ss.clear();
            ss << x;
            
            list += " ";
            list = list + ss.str();
            
            ss.str("");
            ss.clear();
            for(int z = 0; z <= 50; ++z)
            {temp2[z] = '\0';}
            input >> temp;
        }
        ss = stringstream(list);
        
        while(ss >> x)
        {
            root->edges_vector.push_back(pointers_array[x]);
            ss >> x;
            root->labels_vector.push_back(x);
        }
        
        x = 0, y = 0, i = 0, j = 0, k = 0;
        bool flag;
        list = "";
        ss.str("");
        ss.clear();
        for(int z = 0; z <= 50; ++z)
        {temp2[z] = '\0';}
        
        for(int i = 1; i < size; ++i)
        {
            flag = true;
            input >> temp;
            pointers_array[i]->value = atoi(temp);
            if(pointers_array[i]->value == 0)
            {
                if(i < (size-1))
                {
                    while(temp[0] != 'T')
                    {
                        input >> temp;
                    }
                }
                list = "";
                ss.str("");
                ss.clear();
                if(i != (size-1))
                {
                    continue;
                }
                else
                    break;
            }
            
            while(true)
            {
                if(flag == true)
                {
                    input >> temp;
                    flag = false;
                }
                for(j = 0; temp[j] != '('; ++j)
                {
                    temp2[j] = temp[j];
                }
                ++j;
                if(pointers_array[atoi(temp2)] == nullptr)
                {
                    x = atoi(temp2);
                    ss << x;
                    list = list + ss.str();
                    pointers_array[atoi(temp2)] = new Node();
                    pointers_array[atoi(temp2)]->number = atoi(temp2);
                    for(int z = 0; z <= 50; ++z)
                    {temp2[z] = '\0';}
                    for(j, k = 0; temp[j] != ')'; ++j, ++k)
                    {
                        temp2[k] = temp[j];
                    }
                    x = atoi(temp2);
                    ss.str("");
                    ss.clear();
                    ss << x;
                                        
                    list += " ";
                    list = list + ss.str();
                    list += " ";
                    ss.str("");
                    ss.clear();
                    for(int z = 0; z <= 50; ++z)
                    {temp2[z] = '\0';}
                    input >> temp;
                }
                else
                {
                    x = atoi(temp2);
                    ss << x;
                    list = list + ss.str();
                    for(int z = 0; z <= 50; ++z)
                    {temp2[z] = '\0';}
                    for(j, k = 0; temp[j] != ')'; ++j, ++k)
                    {
                        temp2[k] = temp[j];
                    }
                    x = atoi(temp2);
                    ss.str("");
                    ss.clear();
                    ss << x;
                                        
                    list += " ";
                    list = list + ss.str();
                    list += " ";
                    ss.str("");
                    ss.clear();
                    for(int z = 0; z <= 50; ++z)
                    {temp2[z] = '\0';}
                    input >> temp;
                }
                
                if(temp[0] == 'T')
                {
                
                    ss = stringstream(list);
            
                    while(ss >> x)
                    {
                        pointers_array[i]->edges_vector.push_back(pointers_array[x]);
                        ss >> x;
                        pointers_array[i]->labels_vector.push_back(x);
                    }
                    
                    list = "";
                    ss.str("");
                    ss.clear();
                    break;
                }
            }
        }
    }
    for(int i = 0; i < size; ++i)
    {
        pointers_array[i]->value = pointers_array[i]->edges_vector.size();
    }
    input.close();
}

Graph::~Graph(){
    for(int i = (size-1); i >= 0; --i)
    {
        delete pointers_array[i];
    }
}

void Graph::printGraph() {
    int count;
    cout << graph_name << " " << size << endl;
    for(int i = 0; i < size; ++i)
    {
        cout << "T" << i << " " << pointers_array[i]->value << " ";
        count = pointers_array[i]->edges_vector.size();
        for(int j = 0; j < count; ++j)
        {
            cout << pointers_array[i]->edges_vector[j]->number << "(";
            cout << pointers_array[i]->labels_vector[j] << ") ";
        }
        cout << endl;
    }
    cout << endl;
 }

int Graph::countEdges() {
    int x = 0;
    for(int i = 0; i < size; ++i)
    {
        x += pointers_array[i]->value;
    }
    return x;
}
 
void Graph::kruskal() {
    int edges_amount = countEdges();
    Edge edges_array[edges_amount];
    for(int i = 0, k = 0; i < this->size; ++i)
    {
        for(int j = 0; j < pointers_array[i]->edges_vector.size(); ++j)
        {
            edges_array[k].source = pointers_array[i]->number;
            edges_array[k].destination = pointers_array[i]->edges_vector[j]->number;
            edges_array[k].weight = pointers_array[i]->labels_vector[j];
            ++k;
        }
    }
    std::sort(edges_array, edges_array + edges_amount, comparator);
    bool truths_array[edges_amount];
    for(int i = 0; i < edges_amount; ++i)
    {
        truths_array[i] = false;
    }
    vector<int> sets[this->size];
    for(int i = 0; i < this->size; ++i){ sets[i].push_back(i); }
    int node_1 = 0;
    int node_2 = 0;
    for(int i = 0; i < 13; ++i)
    {
        for(int j = 0; j < this->size; ++j)
        {
            if(std::count(sets[j].begin(), sets[j].end(), edges_array[i].source) == 0)
            {
                ;
            }
            else
            {
                node_1 = j;
                break;
            }
        }
        for(int j = 0; j < this->size; ++j)
        {
            if(std::count(sets[j].begin(), sets[j].end(), edges_array[i].destination) == 0)
            {
                ;
            }
            else
            {
                node_2 = j;
                break;
            }
        }
        if(node_1 < node_2)
        {
            for(int j = 0; j < sets[node_2].size(); ++j)
            {
                sets[node_1].push_back(sets[node_2].at(j));
            }
            sets[node_2].clear();
            truths_array[i] = true;
        }
        if(node_1 > node_2)
        {
            for(int j = 0; j < sets[node_1].size(); ++j)
            {
                sets[node_2].push_back(sets[node_1].at(j));
            }
            sets[node_1].clear();
            truths_array[i] = true;
        }
        if(node_1 == node_2)
        {
            truths_array[i] = false;
            continue;
        }
    }
    cout << "The minimum spanning tree will consist of all the nodes" << endl;
    cout << "and those following edges (Kruskal's algorithm):" << endl;
    cout << "Source:         Destination:         Label:" << endl;
    for(int i = 0; i < edges_amount; ++i)
    {
        if(truths_array[i] == true)
        {
            cout << edges_array[i].source << "             " << edges_array[i].destination << "               " << edges_array[i].weight << endl;
        }
    }
}

void Graph::prim() {
    bool visits_array[size];
    for(int i = 0; i < size; ++i)
    {
        visits_array[i] = false;
    }
    std::priority_queue<Edge, std::vector<Edge>, Compare> queue;
    Edge temp, temp2;
    for(int i = 0; i < pointers_array[0]->edges_vector.size(); ++i)
    {
        temp.source = 0;
        temp.destination = pointers_array[0]->edges_vector[i]->number;
        temp.weight = pointers_array[0]->labels_vector[i];
        queue.push(temp);
    }
    visits_array[0] = true;
    cout << "The minimum spanning tree will consist of all the nodes" << endl;
    cout << "and those following edges (Prim's algorithm, started with the root):" << endl;
    cout << "Source:         Destination:         Label:" << endl;
    while(queue.empty() == false)
    {
        temp2 = queue.top();
        if(visits_array[temp2.destination] == false)
        {
            cout << temp2.source << "             " << temp2.destination << "               " << temp2.weight << endl;
            queue.pop();
            for(int i = 0; i < pointers_array[temp2.destination]->edges_vector.size(); ++i)
            {
                temp.source = temp2.destination;
                temp.destination = pointers_array[temp2.destination]->edges_vector[i]->number;
                temp.weight = pointers_array[temp2.destination]->labels_vector[i];
                queue.push(temp);
            }
            visits_array[temp2.destination] = true;
        }
        else
        {
            queue.pop();
        }
    }
}
