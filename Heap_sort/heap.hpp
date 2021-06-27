using namespace std;

class Heap {
private:
    int heap_size;
    int max_size;
    void heapify(int);
public:
    int * array;
    Heap();
    Heap(int max_size);
    bool empty();
    bool check();
    int size();
    void print();
    void push(int x);
    int pop();
    int& top();
    void build(int[], int);
    void sortIter();
}; 
