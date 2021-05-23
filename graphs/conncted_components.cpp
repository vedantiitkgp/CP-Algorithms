// https://cp-algorithms.com/graph/search-for-connected-components.html
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

void dfs(vvi adj,int i,vi &comp,vb &visited)
{
    visited[i] = true;
    comp.push_back(i);
    for(int u: adj[i])
    {
        if(!visited[u])
        {
            dfs(adj,u,comp,visited);
        }
    }
}

void find_connected_componenets(vvi adj,int n)
{
    vb visited(n+1,false);
    vi comp;
    for(int i=1;i<=n;i++)
    {
        if(!visited[i])
        {
            comp.clear();
            dfs(adj,i,comp,visited);
            for(int j=0;j<comp.size();j++) cout<<comp[j]<<" ";
            cout<<endl;
        }
    }
}

int main()
{
    int n,e;
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
    find_connected_componenets(adj,n);
    return 0;
}