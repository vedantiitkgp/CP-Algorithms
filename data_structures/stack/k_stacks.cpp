//https://www.geeksforgeeks.org/efficiently-implement-k-stacks-single-array/
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

//Space effecient implementation
class kStacks
{
    int* arr; //Array of size n storing actual data
    int *top; //Array of size k storing index of top value of stacks
    int* next; //Array of size n used to store next entry for filled or free
    int n,k;
    int free;
public:
    kStacks(int k,int n); //Constructor
    bool isFull() {return (free == -1);}
    void push(int item,int sn);
    int pop(int sn);
    bool isEmpty(int sn) {return (top[sn]==-1);}
};

kStacks::kStacks(int k1,int n1)
{
    k = k1;
    n = n1;
    arr = new int[n];
    top = new int[k];
    next = new int[n];

    //Intialize all stacks
    for(int i=0;i<k;i++)
    {
        top[i] = -1;
    }
    free = 0; //All spaces are free
    for(int i=0;i<n-1;i++)
    {
        next[i] = i+1;
    }
    next[n-1] = -1;
}

void kStacks::push(int item,int sn)
{
    if(isFull())
    {
        cout<<"Stack overflow"<<endl;
    }
    int i = free; // Store index of free slot
    free = next[i];
    next[i] = top[sn]; //Next entry for filled element
    top[sn] = i; //update the top
    arr[i] = item;
}

int kStacks::pop(int sn)
{
    if(isEmpty(sn))
    {
        cout<<"Stack underflow"<<endl;
        return -1;
    }
    int i = top[sn];
    int item = arr[i];
    top[sn] = next[i];
    next[i] = free;
    free = i;
    return item;
}

int main()
{
    // Let us create 3 stacks in an array of size 10
    int k = 3, n = 10;
    kStacks ks(k, n);

    // Let us put some items in stack number 2
    ks.push(15, 2);
    ks.push(45, 2);

    // Let us put some items in stack number 1
    ks.push(17, 1);
    ks.push(49, 1);
    ks.push(39, 1);

    // Let us put some items in stack number 0
    ks.push(11, 0);
    ks.push(9, 0);
    ks.push(7, 0);

    cout << "Popped element from stack 2 is " << ks.pop(2) << endl;
    cout << "Popped element from stack 1 is " << ks.pop(1) << endl;
    cout << "Popped element from stack 0 is " << ks.pop(0) << endl;
    return 0;
}