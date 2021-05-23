// https://cp-algorithms.com/string/prefix-function.html
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

//Online Algorithm
vi prefix(string s)
{
    int n = s.length();
    vi  pi(n);
    pi[0] = 0;
    for(int i=1;i<n;i++)
    {
        int j = pi[i-1];
        if(j>0 && s[i]!=s[j]) j = pi[j-1];
        else if(s[i]==s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vi kmp(string s,string t)
{
    vi occur;
    vi pi = prefix(s);
    if(s.length()>t.length()) return occur;
    int j=0,i=0;
    while(i<t.length())
    {
        if(t[i]==s[j])
        {
            j++;
            i++;
        }
        else
        {
            if(j>0) j = pi[j-1];
            else i++;
        }
        if(j==s.length()) 
        {
            occur.push_back(i-j);
            j = pi[j-1];
        }
    }
    return occur;
}

//Counting length of each prefix
vi prefix_counter(string s)
{
    int n = s.length();
    vi ans(n+1,0); // Counting the length of prefix
    vi pi = prefix(s);
    for(int i=0;i<n;i++)
    {
        ans[pi[i]]++;
    }
    for(int i = n-1;i>0;i--)
    {
        ans[pi[i-1]]+= ans[i];
    }
    for(int i=0;i<=n;i++) ans[i]++;
    return ans;
}

//Helper functions calculating prefix which reappears
int longest_prefix_re(string s)
{
    vi prefix_count = prefix_counter(s);
    int n = s.length();
    int max_prefix = 0;
    for(int i=1;i<n;i++) max_prefix = max(max_prefix,prefix_count[i]-1);
    return max_prefix;
}

// O(n^2) algorithm counting diffrent substrings
ll different_substrings(string s)
{
    ll ans = 1;
    string sub,rev;
    int n = s.length();
    for(int i=1;i<n;i++)
    {
        sub = s.substr(0,i+1);
        reverse(sub.begin(),sub.end());
        ans+=i+1-longest_prefix_re(sub);
    }
    return ans;
}


int main()
{
    string s,t;
    s = "maa";
    t = "maakaladlabigadgayamaa";
    vi occur = kmp(s,t);
    //for(int i=0;i<occur.size();i++) cout<<occur[i]<<" ";
    //cout<<endl;
    cout<<different_substrings(s)<<endl;
    return 0;
}

