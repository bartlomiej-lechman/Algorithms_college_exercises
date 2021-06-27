#include "heap.cpp"
#include <fstream>

using namespace std;

int main()
{
    ifstream input;
    input.open("input.txt");
    int values_number = 0, temp = 0;
    while(input >> temp) { ++values_number; }
    int array[values_number] = {0};
    input.clear();
    input.seekg(0, ios::beg);
    for(int i = 0; i < values_number; ++i)
    {
        input >> array[i];
    }
    input.close();
    Heap heap(values_number);
    heap.build(array, values_number);
    heap.sortIter();
    cout << "Writing sorted data to a file..." << endl;
    ofstream output;
    output.open("output.txt");
    for(int i = 1; i <= values_number; ++i)
    {
        output << heap.array[i] << endl;
    }
    output.close();
    return 0;
}
