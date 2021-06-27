#include "graph.hpp"
#include "node.hpp"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <stack>
#include <queue>

using namespace std; 

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
    Node helper;
    int helper_integer;
    for(int i = 0; i < size; ++i)
    {
        helper = *(pointers_array[i]);
        for(int j = 0; j < pointers_array[i]->edges_vector.size(); ++j)
        {
            helper_integer = helper.edges_vector.at(j)->number;
            pointers_array[helper_integer]->parents_vector.push_back(pointers_array[i]);
        }
    }
}

Graph::~Graph(){
    for(int i = (size-1); i >= 0; --i)
    {
        delete pointers_array[i];
    }
}

void Graph::dijkstra(int source) {
    int neighborhood_matrix[size][size] = {{0}};
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < pointers_array[i]->edges_vector.size(); ++j)
        {
            neighborhood_matrix[i][pointers_array[i]->edges_vector[j]->number] = pointers_array[i]->labels_vector[j];
        }
    }
    int distance[size];
    bool visits_array[size]; 
  
    for(int i = 0; i < size; i++) { distance[i] = 2147483647, visits_array[i] = false; } 
    
    distance[source] = 0; 
  
    for(int i = 0; i < size - 1; ++i) 
    { 
        int u = minDistance(distance, visits_array, size); 
        visits_array[u] = true; 
        for(int j = 0; j < size; ++j) 
        {
            if(!visits_array[j] && neighborhood_matrix[u][j] && (distance[u] != 2147483647) 
                && (distance[u] + neighborhood_matrix[u][j] < distance[j]) )
            {
                distance[j] = distance[u] + neighborhood_matrix[u][j]; 
            }
        }
    }
    cout << "Total distance from root to all nodes:" << endl; 
    for (int i = 0; i < size; i++)
    {
         cout << i << " - " << distance[i] << endl;
    }        
}


int Graph::minDistance(int distance[], bool visits_array[], int size) 
{ 
    int min = 2147483647, min_index; 
  
    for(int i = 0; i < size; ++i) 
    {
        if( (visits_array[i] == false) && (distance[i] <= min) ) 
        {
            min = distance[i];
            min_index = i;
        }
    }
    
    return min_index; 
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
