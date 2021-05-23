//https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/

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

class Queue
{
public:
    int front,rear,size;
    int capacity;
    int* array;
};

Queue* createQueue(int capacity)
{
    Queue* queue = new Queue();
    queue->capacity = capacity;
    queue->array = new int[capacity];
    queue->front = 0;
    queue->size = 0;
    queue->rear = capacity-1;
    return queue;
}

bool isEmpty(Queue* q)
{   
    if(q->size==0) return true;
    else return false;
}

bool isFull(Queue *q)
{
    if(q->size == q->capacity) return true;
    else return false;
}

void enqueue(Queue *q,int item)
{
    if(isFull(q)) return;
    q->rear = (q->rear+1)%q->capacity;
    q->array[q->rear] = item;
    q->size +=1;
    cout<<item<<" enqueued to queue"<<endl;
}

int dequeue(Queue *q)
{
    if(isEmpty(q)) return -1;
    int item = q->array[q->front];
    cout<<item<<endl;
    q->front = (q->front +1)%q->capacity;
    q->size -= 1;
    return item;
}

int front(Queue *q)
{
    if(isEmpty(q)) return -1;
    return q->array[q->front];
}

int rear(Queue *q)
{
    if(isEmpty(q)) return -1;
    return q->array[q->rear];
}

int main()
{
    Queue* queue = createQueue(1000);
 
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
 
    cout << dequeue(queue)
         << " dequeued from queue\n";
 
    cout << "Front item is "
         << front(queue) << endl;
    cout << "Rear item is "
         << rear(queue) << endl;
    cout<<queue->front<<" "<<queue->rear<<endl;
    return 0;
}