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

//Basic trial test
string is_prime(ll x)
{
    for(ll i=2;i*i<=x;i++)
    {
        if(x%i==0) return "No";
    }
    return "Yes";
}

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

//Check Fermality test
string fermality_test(ll n,ll iter = 10)
{
    if(n<4)
    {
        if(n==2||n==3) return "Yes";
        else return "No";
    }
    for(ll i=0;i<iter;i++)
    {
        ll a = 2 + rand()%(n-3);
        if(bin_pow(a,n-1,n)!=1) return "No";
    }
    return "Yes";
}


int main()
{
    ll x;
    cin>>x;
    //cout<<"Is it prime ? "<<is_prime(x)<<endl;
    cout<<"Is it prime ? "<<fermality_test(x)<<endl;
    return 0;
}