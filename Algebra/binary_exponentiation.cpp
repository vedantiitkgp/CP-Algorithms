// https://cp-algorithms.com/algebra/binary-exp.html#toc-tgt-5

#include<bits/stdc++.h>

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

// Applications of Binary exponenetiation

/*
// (Modular Computation of binary power)

ll bin_pow(ll a,ll b,ll m)
{
    a = a%m;
    ll res=1;
    while(b>0)
    {
        if(b&1)
        {
            res = (res * a)%m;
        }
        a = (a * a)%m;
        b = b>>1; 
    }
    return res;
}
*/

/*
// (Fibonacci Number Calculation)

void multiply(vvl &F,vvl &M)
{
    int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
     
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(vvl &F,ll n)
{
    if(n==0 || n==1)return;
    vvl M(2,vl(2));
    M[0][0] = 1;
    M[0][1] = 1;
    M[1][0] = 1;
    M[1][1] = 0;
    power(F,n/2);
    multiply(F,F);
    if(n%2!=0)
    {
        multiply(F,M);
    }
}

ll fib(ll n)
{
    if(n==0) return 0;
    vvl F(2,vl(2));
    F[0][0] = 1;
    F[0][1] = 1;
    F[1][0] = 1;
    F[1][1] = 0;
    power(F,n-1);
    return F[0][0];
}
*/

/*
ll binary_exponent(ll a,ll b)
{
    ll res=1;
    while(b>0)
    {
        if(b&1)
        {
            res = res * a;
        }
        a = a * a;
        b = b>>1; 
    }
    return res;
}

*/

/*
(Multiplying Matrices to the power k)
-> No of of path lengths k in the graph - Multiplying Ajacent matrix A to power k and value of Aij
-> Making opeartions to coordinates system 
*/

int main()
{
    ll a,b,n;
    cin>>a>>b;
    //cout<<binary_exponent(a,b)<<endl;
    cout<<bin_pow(a,b,1000000007)<<endl;
    //cin>>n;
    //cout<<fib(n)<<endl;
    return 0;
}


