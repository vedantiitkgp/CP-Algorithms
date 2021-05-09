//https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
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

class Stack
{
    int top; //Top element
public:
    int a[MAX]; //Array storing elements

    Stack() //Constructor
    {
        top = -1;
    }
    bool push(int x); //Push a new element
    int pop(); //Pop the top element
    int peek(); // Return the topmost element
    bool isEmpty(); //Check if empty or not

};

bool Stack::push(int x)
{
    if(top>=(MAX-1))
    {
        cout<<"Stack overflow"<<endl;
        return false;
    }
    a[++top] = x;
    cout<<"Pushed into stack"<<endl;
    return true;
}

int Stack::pop()
{
    if(top<0)
    {
        cout<<"Stack underflow"<<endl;
        return 0;
    }
    int x = a[top--];
    return x;
}

int Stack::peek()
{
    if(top<0)
    {
        cout<<"Stack emepty"<<endl;
        return -1;
    }
    int x = a[top];
    return x;
}

bool Stack::isEmpty()
{
    return(top<0);
}

int main()
{
    class Stack s;
    s.push(10);
    s.push(20);
    s.push(30);
    cout << s.pop() << " Popped from stack\n";
    //print all elements in stack :
    cout<<"Elements present in stack : ";
    while(!s.isEmpty())
    {
        // print top element in stack
        cout<<s.peek()<<" ";
        // remove top element in stack
        s.pop();
    }
    cout<<endl;
    return 0;
}