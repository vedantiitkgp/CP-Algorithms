// https://www.geeksforgeeks.org/binary-heap/
// https://www.geeksforgeeks.org/time-complexity-of-building-a-heap/

#include<bits/stdc++.h>
#define MAX 1000

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<string, string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<ll> vl;
typedef vector<vl> vvl;

void swap(int *x,int *y);

class MinHeap
{
    int* harr; //pointer to array of elements
    int capacity; //Maximum capacity of heap
    int heap_size; //Current no of elememts of heap
public:
    MinHeap(int capacity);
    void MinHeapify(int i);
    int parent(int i) { return (i-1)/2;}
    int left(int i) { return (2*i+1);}
    int right(int i) { return (2*i+2);}
    int extractMin(); //extract the root - O(logn) time
    void decreaseKey(int i,int new_val); //decrease key value at index - O(logn) time
    int getMin() {return harr[0];} //return value at root
    void deleteKey(int i); //Delete a key stored at index i - O(logn) time
    void insertKey(int k); //insert a new key 'k' - O(logn) time
};

MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}

void swap(int *x,int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if(l<heap_size && harr[l]<harr[i])
        smallest = l;
    if(r<heap_size && harr[r]<harr[smallest])
        smallest = r;
    if(smallest!=i)
    {
        swap(&harr[i],&harr[smallest]);
        MinHeapify(smallest);
    }
}

int MinHeap::extractMin()
{
    if(heap_size<=0) return INT_MAX;
    else if(heap_size==1)
    {
        heap_size--;
        return harr[0];
    }
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);
    return root;
}

void MinHeap::decreaseKey(int i,int new_val)
{
    harr[i] = new_val;
    while(i!=0 && harr[parent(i)]>harr[i])
    {
        swap(&harr[i],&harr[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::insertKey(int k)
{
    if(heap_size==capacity)
    {
        cout<<"Overflow :: could not insert key"<<endl;
        return;
    }
    cout<<"Insert "<<k<<" key"<<endl;
    heap_size++;
    int i = heap_size-1;
    harr[i] = k;
    while(i!=0 && harr[parent(i)]>harr[i])
    {
        swap(&harr[i],&harr[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::deleteKey(int i)
{
    decreaseKey(i,INT_MIN);
    extractMin();
}

int main()
{
    MinHeap h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    cout<<"Removed Minimum root element : "<<h.extractMin()<<endl;
    cout<<"Minimum root element : "<<h.getMin()<<endl;
    h.decreaseKey(2, 1);
    cout<<"Minimum root element : "<<h.getMin()<<endl;
    return 0;
}

// Applications :
// 1. Heapsort
// 2. Priority queue
// 3. Graph Algorithms - Prim's Algorithm, Djikstra Algorithm
// 4. Effecient solved - K'th largest element, Merge k sorted arrays
