// https://cp-algorithms.com/data_structures/disjoint_set_union.html

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
typedef vector<bool> vb;

// Path compression optimization applied and Union by size (Similar union by rank)

void swap(vi &a, vi &b)
{
    vi temp;
    temp = a;
    a = b;
    b = temp;
}

void make_set(int v, vi &parent,vi &size)
{
    parent[v] = v;
    size[v] = 1;
}

void find_set(int v, vi &parent)
{
    if(v==parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a,int b,vi &parent,vi &size)
{
    a = find_set(a);
    b = find_set(b);
    if(a!=b)
    {
        if(size[a]<size[b]) swap(a,b);
        parent[b] = a;
        size[a]+=size[b];
    }
}

// Applications
// 1. Connected components -  Completing a Minimum spanning tree
// 2. Search connected components in a image.
// 3. Arpa's trick for finding long range minimum queries
// 4. Offline LCA - O(alpha(n))
// 5. Online bridge finding algorithm help