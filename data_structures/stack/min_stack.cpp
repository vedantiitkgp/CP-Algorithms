//https://www.geeksforgeeks.org/design-a-stack-that-supports-getmin-in-o1-time-and-o1-extra-space/
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


//Min in O(1) time and O(1) Space
struct myStack
{
    stack<int> s;
    int minEle;

    int getMin()
    {
        if(s.empty())
        {
            cout<<"Stack is empty"<<endl;
            return -1;
        }
        return minEle;
    }

    void push(int x)
    {   
        if(s.empty())
        {
            s.push(x);
            minEle = x;
        }
        else if(x<minEle)
        {
            s.push(2*x-minEle);
            minEle = x;
        }
        else
        {
            s.push(x);
        }
        return;
    }

    int pop()
    {
        if(s.empty())
        {
            cout<<"Stack underflow"<<endl;
            return -1;
        }

        if(minEle <= s.top())
        {
            int y = s.top();
            s.pop();
            return y;
        }
        else
        {
            int y = s.top();
            s.pop();
            int ans = minEle;
            minEle = 2*minEle -y; 
            return ans;
        }
    }

    int peek()
    {
        if(s.empty())
        {
            cout<<"Stack is empty"<<endl;
            return -1;
        }
        if(minEle<s.top())
        {
            return minEle;
        }
        else
        {
            return s.top();
        }
    }
};


int main()
{
    myStack s;
    s.push(3);
    s.push(5);
    cout<<"Current Minimum is: "<<s.getMin()<<endl;
    s.push(2);
    s.push(1);
    cout<<"Current Minimum is: "<<s.getMin()<<endl;
    cout<<"Top Element removed is: "<<s.pop()<<endl;
    cout<<"Current Minimum is: "<<s.getMin()<<endl;
    cout<<"Top Element removed is: "<<s.pop()<<endl;
    cout<<"Top Element is: "<<s.pop()<<endl;
    return 0;
}