//https://www.geeksforgeeks.org/iterative-tower-of-hanoi/

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

//Iteractive version of traversal

void moveDisk(char s,char d,int disk)
{
    cout<<"Move Disk "<<disk<<" from "<<s<<" to "<<d<<endl;
}

void moveDiskBetweenTwoPoles(stack<int> &src,stack<int> &dest,char s,char d)
{
    int pole1TopDisk,pole2TopDisk;
    if(!src.empty()) pole1TopDisk = src.top();   
    if(!dest.empty()) pole2TopDisk = dest.top();
    
    if(dest.empty()||(pole1TopDisk<pole2TopDisk))
    {
        src.pop();
        dest.push(pole1TopDisk);
        moveDisk(s,d,pole1TopDisk);
    }
    else if(src.empty()||(pole1TopDisk>pole2TopDisk))
    {
        dest.pop();
        src.push(pole2TopDisk);
        moveDisk(d,s,pole2TopDisk);
    }
}   

void tohInteractive(int n,stack<int> &src,stack<int> &aux,stack<int> &dest)
{
    char s,a,d,temp;
    s = 'S';
    a = 'A';
    d = 'D';
    ll number_moves = pow(2,n) -1;
    
    if(n%2==0)
    {
        temp = s;
        s = a;
        a = temp;
    }

    for(int i=n;i>=1;i--) src.push(i);

    for(ll i=1;i<=number_moves;i++)
    {
        if(i%3==1) moveDiskBetweenTwoPoles(src,dest,s,d);
        else if(i%3==2) moveDiskBetweenTwoPoles(src,aux,s,a);
        else if(i%3==0) moveDiskBetweenTwoPoles(aux,dest,a,d);
    }
}

int main()
{
    int n;
    cin>>n;
    stack <int> src,aux,dest;
    tohInteractive(n,src,aux,dest);
    return 0;
}