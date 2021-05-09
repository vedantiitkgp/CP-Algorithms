//https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html

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

// Optimized Simple Seive
vl simple_seive(ll n)
{
    vl ans;
    ll i,j;
    vector<bool> is_prime(n,true);

    //Running for 2
    ans.push_back(2);
    for(j=4;j<=n;j+=2)
    {
        is_prime[j] = false;
    }

    //Running for 3+
    for(i=3;i*i<=n;i+=2)
    {
        if(is_prime[i]==false) continue;
        ans.push_back(i);
        for(j=i*i;j<=n;j+=i)
        {
            is_prime[j] = false;
        }
    }

    for(j=i;j<=n;j++)
    {
        if(is_prime[j]) ans.push_back(j);
    }
    return ans;
}


//Optimized Segemented Seive
vl segmented_seive(ll n)
{  
    vl ans;
    ll limit = floor(sqrt(n))+1;
    vl prime_sqrt = simple_seive(limit);
    ans = prime_sqrt;
    ll low = limit;
    ll high = 2*limit;
    while(low<n)
    {
        if(high>=n) high = n;
        vector<bool> mark(limit+1,true);
        for(ll i=0;i<prime_sqrt.size();i++)
        {
            ll lolim = floor(low/prime_sqrt[i])*prime_sqrt[i];
            if(lolim<low) lolim += prime_sqrt[i];
            for(ll j=lolim;j<high;j+=prime_sqrt[i])
            {
                mark[j-low] = false;
            } 
        }
        for(ll i=low;i<high;i++)
        {
            if(mark[i-low]) ans.push_back(i);
        }
        low+=limit;
        high+=limit;
    }
    return ans;
}

// Segmented Seive for particular range
vl segmented_seive_range(ll l,ll r)
{  
    vl ans;
    ll limit = floor(sqrt(r))+1;
    vl prime_sqrt = simple_seive(limit);
    if(l<=1) l = 2;
    ll low = l;
    ll high = r;
    vector<bool> mark(r-l+1,true);
    for(ll i=0;i<prime_sqrt.size();i++)
    {
        ll lolim = floor(low/prime_sqrt[i])*prime_sqrt[i];
        if(lolim<low) lolim += prime_sqrt[i];
        for(ll j=lolim;j<high;j+=prime_sqrt[i])
        {
            mark[j-low] = false;
        } 
    }
    for(ll i=low;i<high;i++)
    {
        if(mark[i-low]) ans.push_back(i);
    }
    return ans;
}


void print_prime(vl ans,vl val,bool range)
{   
    if(!range)cout<<"Primes till "<<val[0]<<endl;
    else 
    {
        cout<<"Primes from "<<val[0]<<" to "<<val[1]<<endl;
    }
    for(ll i=0;i<ans.size();i++)
    {
        cout<< ans[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    vl val;
    
    ll n;
    cin>>n;
    vl ans = simple_seive(n);
    //Optimized for Space and Time Complexity
    //vl ans = segmented_seive(n);
    val.push_back(n);
    print_prime(ans,val,false);
    
    /*
    ll l,r;
    //Optimized for Space and Time Complexity for range
    cin>>l>>r;
    vl ans = segmented_seive_range(l,r);
    val.push_back(l);
    val.push_back(r);
    print_prime(ans,val,true);
    */
    return 0;
}

//https://cp-algorithms.com/algebra/prime-sieve-linear.html (Seive working in linear capacity)