// https://cp-algorithms.com/algebra/extended-euclid-algorithm.html

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

ll extended_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll x1,y1;
    ll d = extended_gcd(b,a%b,x1,y1);
    x = y1;
    y = x1- y1*(a/b);
    return d;
}

int main()
{
    ll x,y,a,b;
    cin>>a>>b;
    cout<<"GCD of Numbers :"<<extended_gcd(a,b,x,y)<<endl;
    cout<<"GCD Coeffecients:"<<x<<" "<<y<<endl;
    return 0;
}