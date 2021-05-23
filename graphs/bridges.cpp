// https://cp-algorithms.com/graph/bridge-searching.html
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

//Online Algorithm





//Offline Algorithm

void is_bridge(int u,int v)
{
    cout<<u<<" "<<v<<endl;
}

void dfs_mod(vvi adj,int u,vi &low,vi &tin,vb &visited,int &timer,int p=-1)
{
    visited[u] = true;
    tin[u] = low[u] = timer++;
    for(int v:adj[u])
    {
        if(v==p) continue;
        else if(visited[v])
        {
            low[u] = min(low[u],tin[v]); 
        }
        else
        {
            dfs_mod(adj,v,low,tin,visited,timer,u);
            low[u] = min(low[u],low[v]);
            if(low[v]>tin[u]) is_bridge(u,v);
        }
    }
}

void find_bridges_off(vvi adj,int n)
{
    int timer =0;
    vi low(n+1,-1);
    vi tin(n+1,-1);
    vb visited(n+1,false);
    for(int i=1;i<=n;i++)
    {
        if(!visited[i])
        {
            dfs_mod(adj,i,low,tin,visited,timer);
        }
    }
}

int main()
{
    int n,s,e;
    cout<<"Enter the no of vertices and no of edges :"<<endl;
    cin>>n>>e;
    vvi adj(n+1);
    cout<<"Define edges :"<<endl;
    int param1,param2;
    for(int i=0;i<e;i++)
    {
        cin>>param1>>param2;
        adj[param1].push_back(param2);
    }
    cout<<"Bridges"<<endl;
    find_bridges_off(adj,n);
    return 0;
}
// Applications
// 1. Converting Undirected graphs to SCC forming strong orientation