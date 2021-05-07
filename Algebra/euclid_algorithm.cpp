//https://cp-algorithms.com/algebra/euclid-algorithm.html

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

ll gcd(ll a,ll b)
{
    if(b==0) return a;
    else return gcd(b,a%b);
}

ll lcm(ll a,ll b)
{
    return (a*b)/gcd(a,b);
}

/*
(Fast GCD calculating function using some properties)
int gcd(int a, int b) {
    if (!a || !b)
        return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b)
            swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}
*/


int main()
{
    ll a,b;
    cin>>a>>b;
    cout<<"GCD of these two are :"<<gcd(a,b)<<endl;
    cout<<"LCM of these two are :"<<lcm(a,b)<<endl;
    return 0;
}
