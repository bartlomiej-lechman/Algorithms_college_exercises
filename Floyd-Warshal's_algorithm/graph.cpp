#include "graph.hpp"
#include "node.hpp"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std; 

Graph::Graph()
{
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
    int helper_number;
    for(int i = 0; i < size; ++i)
    {
        helper = *(pointers_array[i]);
        for(int j = 0; j < pointers_array[i]->edges_vector.size(); ++j)
        {
            helper_number = helper.edges_vector.at(j)->number;
            pointers_array[helper_number]->parents_vector.push_back(pointers_array[i]);
        }
    }
}

void Graph::floydWarshal() {
    int graph[size][size];
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            graph[i][j] = 999999;
        }
    }
    for(int i = 0; i < size; ++i)
    {
        graph[i][i] = 0;
    }
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < pointers_array[i]->edges_vector.size(); ++j)
        {
            graph[i][pointers_array[i]->edges_vector[j]->number] = pointers_array[i]->labels_vector[j];
        }
    }
    for(int k = 0; k < size; ++k)
    {
        for(int i = 0; i < size; ++i)
        {
            for(int j = 0; j < size; ++j)
            {
                if(graph[i][j] > graph[i][k] + graph[k][j]){ graph[i][j] = graph[i][k] + graph[k][j]; }
            }
        }
    }
    
    
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            printf("%10d ", graph[i][j]);
        }
        printf("\n");
    }
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
