// https://cp-algorithms.com/graph/topological-sort.html
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

void dfs(vvi adj,int u,vi &result,vb &visited)
{
    visited[u] = true;
    for(int v:adj[u])
    {
        if(!visited[v])
        {
            dfs(adj,v,result,visited);
        }
    }
    result.push_back(u);
}

void find_topological_order(vvi adj,int n)
{
    vb visited(n+1,false);
    vi result;
    for(int i=1;i<=n;i++)
    {
        if(!visited[i]) dfs(adj,i,result,visited);
    }
    reverse(result.begin(),result.end());
    for(int i=0;i<result.size();i++)
    {
        cout<<result[i]<<" ";
    }
    cout<<endl;
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
    cout<<"Topological Order :"<<endl;
    find_topological_order(adj,n);
    return 0;
}