//https://www.geeksforgeeks.org/design-a-stack-with-find-middle-operation/
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

//Defining a double linked linked list
class DLLNode
{
public:
    DLLNode* prev;
    int data;
    DLLNode* next;
};

//Defining a stack
class myStack
{
public:
    int count;
    DLLNode* head;
    DLLNode* mid;
};

myStack* createMyStack()
{
    myStack* ms = new myStack();
    ms->count =0;
    return ms;
}

void push(myStack* ms,int new_data)
{
    //Allocate new node to be added to beginning]
    DLLNode* newDLLNode = new DLLNode();
    newDLLNode->data = new_data;
    newDLLNode->prev = NULL;
    newDLLNode->next = ms->head;
    ms->count +=1;

    if(ms->count ==1) ms->mid = newDLLNode;
    else
    {
        ms->head->prev = newDLLNode;
        if(!(ms->count&1))ms->mid = ms->mid->prev; //Check for even
    }
    ms->head = newDLLNode;
}

int pop(myStack* ms)
{
    if(ms->count==0)
    {
        cout<<"Stack Underflow"<<endl;
        return -1;
    }
    ms->count -=1;
    int item = ms->head->data;
    ms->head = ms->head->next;
    if(ms->head!=NULL) ms->head->prev = NULL;
    if ((ms->count) & 1) ms->mid = ms->mid->next; //Check for odd
    return item;
}

int findMiddle(myStack* ms)
{
    if(ms->count==0)
    {
        cout<<"Stack Empty"<<endl;
        return -1;
    }
    return ms->mid->data;
}

int deleteMiddle(myStack* ms)
{
    int temp = ms->mid->data;
    ms->mid->prev->next = ms->mid->next;
    ms->mid->next->prev = ms->mid->prev;
    ms->count -=1;
    delete ms->mid;
    return temp;
}

bool isEmpty(myStack* ms)
{
    if(ms->count>0) return false;
    else return true;
}

int main()
{
    myStack* ms = createMyStack();
    push(ms, 11);
    push(ms, 22);
    push(ms, 33);
    push(ms, 44);
    push(ms, 55);
    push(ms, 66);
    push(ms, 77);
 
    cout << "Item popped is " << pop(ms) << endl;
    cout << "Item popped is " << pop(ms) << endl;
    cout << "Middle Element is " << findMiddle(ms) << endl;
    cout<<"deleted mid element "<<deleteMiddle(ms)<<endl;
    while(!isEmpty(ms))
    {
        cout<<pop(ms)<<endl;
    }
    return 0;
}