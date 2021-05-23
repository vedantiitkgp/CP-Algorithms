// https://cp-algorithms.com/graph/cutpoints.html
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

void dfs_cut(vvi adj,int u,vi &low,vi &tin,vb &visited,int &timer,int p=-1)
{
    visited[u] = true;
    low[u] = tin[u] = timer++;
    int children =0;
    for(int v:adj[u])
    {
        if(v==p)continue;
        else if(visited[v])
        {
            low[u] = min(low[u],tin[v]);
        }
        else
        {
            dfs_cut(adj,v,low,tin,visited,timer,u);
            low[u] = min(low[u],low[v]);
            if(low[v]>=tin[u] && p!=-1)
            {
                cout<<u<<endl;  
            }
            children++;
        }
    }
    if(p==-1&&children>1)
    {
        cout<<u<<endl;
    }
}

void find_cutpoints_off(vvi adj,int n)
{
    vi low(n+1,-1);
    vi tin(n+1,-1);
    vb visited(n+1,false);
    int timer =0;
    for(int i=1;i<=n;i++)
    {
        if(!visited[i]) dfs_cut(adj,i,low,tin,visited,timer);
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
    cout<<"Cutpoints :"<<endl;
    find_cutpoints_off(adj,n);
}