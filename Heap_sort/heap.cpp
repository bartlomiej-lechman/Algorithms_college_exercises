#include <iostream> 
#include "heap.hpp"

using namespace std;

Heap::Heap() : heap_size(0), max_size(100000) {
    array = new int[max_size + 1];
}

Heap::Heap(int max_size) : heap_size(0), max_size(max_size) {
    array = new int[max_size + 1];
}

int Heap::size() {
    return heap_size;
}

bool Heap::empty() {
    if(heap_size == 0)
        return true;
    else
        return false;
}

int & Heap::top() {
    if(heap_size > 0)
    {   
        int & ref = array[heap_size];
        return ref;
    }
    else
    {
        cout << "empty heap" << endl;
        int & ref = array[0];
        return ref;
    }
}

int Heap::pop() {
    if(heap_size > 0)
    {
        int temp = array[heap_size];
        --heap_size;
        return temp;
    }
    else
    {
        cout << "empty heap" << endl;
        return -1;
    }
}

void Heap::heapify(int i) {
    if( (i <= heap_size) && (heap_size > 1))
    {
        int temp_index = i;
        while( (array[temp_index/2] < array[i]) && (temp_index != 0))
        {
            temp_index /= 2;
        }
        int temp_value = array[i];
        for(int j = i; j > temp_index; j /= 2)
        {
            array[j] = array[j/2];
        }
        array[temp_index] = temp_value;
    }
    else
    {
        cout << "wrong index, or empty heap" << endl;
    }
}

void Heap::build(int passed_array[], int size) {
    for(int i = 1; i <= size; ++i)
    {
        array[i] = std::move(passed_array[i-1]);
        ++heap_size;
    }
    for(int i = 1; i <= size; ++i)
    {
        heapify(i);
    }
}

void Heap::push(int x) {
    ++heap_size;
    array[heap_size] = x;
    heapify(heap_size);
}

bool Heap::check() {
    if(heap_size == 0)
    {
        cout << "empty heap" << endl;
        return true;
    }
    else if(heap_size == 1)
    {
        cout << "one element in heap" << endl;
        return true;
    }
    else
    {
        for(int i = 2; i <= heap_size; ++i)
        {
            if(array[i] <= array[i/2])
            {
                ;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
}

void Heap::sortIter() {
    int temp_index = heap_size;
    while(temp_index > 1)
    {   
        std::swap(array[temp_index], array[1]);
        --temp_index;
        for(int i = 1; i <= temp_index; ++i)
        {
            heapify(i);
        }
    }
}

void Heap::print() {
    for(int i = 1; i <= heap_size; ++i)
    {
        cout << array[i] << endl;
    }
}
