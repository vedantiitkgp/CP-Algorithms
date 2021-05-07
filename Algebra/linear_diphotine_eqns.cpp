// https://cp-algorithms.com/algebra/linear-diophantine-equation.html

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<string, string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef vector<ll> vl;
typedef vector<vl> vvl;

ll extended_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x = 1;
        y =0;
        return a;
    }
    ll x1,y1;
    ll g = extended_gcd(b,a%b,x1,y1);
    x = y1;
    y = x1 - y1*(a/b);
    return g; 
}


bool find_soln(ll a,ll b,ll c,ll &x0, ll &y0,ll &g)
{
    g = extended_gcd(a,b,x0,y0);
    if(c%g!=0) return false;
    x0 *= c/g;
    y0 *= c/g;
    if(a<0) x0 = -1*x0;
    if(b<0) y0 = -1*y0;
    return true;
}

vll find_all(ll x0,ll y0,ll a,ll b,ll g,ll n)
{
    vll ans;
    for(ll i=0;i<n;i++)
    {
        ans.push_back({x0+i*(b/g),y0-i*(a/g)});
    }
    return ans;
}

int main()
{
    ll a,b,c,x0,y0,g,n;
    cin>>a>>b>>c;
    cin>>n;
    cout<<"Is there exists ans to the solution ? "<<find_soln(a,b,c,x0,y0,g)<<endl;
    cout<<"Soln to the equations are :"<<endl;
    vll ans = find_all(x0,y0,a,b,g,n);
    for(ll i=0;i<n;i++)
    {
        cout<<ans[i].first<<" "<<ans[i].second<<endl;
    }
    return 0;
}