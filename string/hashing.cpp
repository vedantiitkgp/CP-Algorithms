//https://cp-algorithms.com/string/string-hashing.html
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

ll bin_mod(ll a,ll n,ll m)
{
    a = a%m;
    ll res = 1;
    while(n>0)
    {
        if(n&1)
        {
            res = (res*a)%m;
        }
        a = (a*a)%m;
        n = n>>1;
    }
    return res;
}

ll compute_hash(string &s)
{
    ll p = 31;
    ll m = 1e9 + 9;
    ll ans = 0;
    for(ll i=0;i<s.length();i++)
    {
        ans += ((s[i]-'a'+1)*bin_mod(p,i,m))%m;
    }
    return ans;
}

// Group identical strings 
vector<vector<int> > group_identical(vector<string> &s)
{
    int n = s.size();
    vector<pair<long long,int> > hashes(n);
    for(int i=0;i<n;i++)
        hashes[i] = {compute_hash(s[i]),i};
    sort(hashes.begin(),hashes.end());
    vector<vector<int> > groups;
    for(int i=0;i<n;i++)
    {
        if(i==0||hashes[i].first!=hashes[i-1].first)
            groups.emplace_back();
        groups.back().push_back(hashes[i].second);
    }
    return groups;
}

// Example Tasks :
//1. Searching for duplicate strings 
//2. Fast hash calculation of substrings

//Applications :
// 1. Rabinkarp algorithm for string matching
// 2. Number of diffrent substrings in O(n^2logn)
// 3. Calculate no of palindromic substrings


ll count_substrings(string s)
{
    ll n= s.length();
    ll p = 31; // make it 53 if including uppercase letters
    ll m = 1e9+9;
    vector<ll> p_pow(n);
    p_pow[0] = 1;
    for(int i=1;i<n;i++)
    {
        p_pow[i] = (p*p_pow[i-1])%m;
    }
    vector<ll> h(n+1,0);
    for(int i=0;i<n;i++)
    {
        h[i+1] = (h[i] + (s[i]-'a'+1)*p_pow[i])%m ;  
    }
    int cnt = 0;

    for(int l=1;l<=n;l++)
    {
        set<ll> hs;
        for(int i=0;i<=n-l;i++)
        {
            ll cur_h = (h[i+l] -h[i] + m)%m;
            cur_h = (cur_h * p_pow[n-i-1])%m;
            hs.insert(cur_h);
        }
        cnt +=hs.size(); 
    }
    return cnt;
}


int main()
{
    string a,b,c;
    a = "vinayak";
    b = "vinayak";
    //if(compute_hash(a)==compute_hash(b)) cout<<"Strings are same"<<endl;
    //else cout<<"Strings are diffrent"<<endl;
    c = "goat";
    cout<<count_substrings(c)<<endl;
    return 0;
}

