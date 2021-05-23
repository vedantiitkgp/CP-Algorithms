// https://cp-algorithms.com/graph/depth-first-search.html
// https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
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

void dfs_util(vvi adj,vb &visited,int s,vi &d,vi &p)
{
    visited[s] = true;
    for(int u: adj[s])
    {
        if(!visited[u])
        {
            d[u] = d[s]+1;
            p[u] = s;
            dfs_util(adj,visited,u,d,p);
        }
    }
}

void dfs_recursive(vvi adj,int n,int s,vi &d,vi &p)
{
    vb visited(n+1,false);
    p[s] = -1;
    dfs_util(adj,visited,s,d,p);
}

void dfs_stack(vvi adj,int n,int s,vi &d,vi &p)
{
    stack<int> st;
    vb visited(n+1,false);
    p[s] = -1;
    st.push(s);
    visited[s] = true;
    while(!st.empty())
    {
        int v = st.top();
        st.pop();
        for(int u:adj[v])
        {
            if(!visited[u])
            {
                visited[u] = true;
                d[u] = d[v] + 1;
                p[u] = v;
                st.push(u);
            }
        }
    }
}

int main()
{
    int n,s,e;
    cout<<"Enter the no of vertices and no of edges :"<<endl;
    cin>>n>>e;
    cout<<"Enter the source vertex :"<<endl;
    cin>>s;
    vvi adj(n+1);
    cout<<"Define edges :"<<endl;
    int param1,param2;
    for(int i=0;i<e;i++)
    {
        cin>>param1>>param2;
        adj[param1].push_back(param2);
    }
    vi d(n+1,0);//Distance vector
    vi p(n+1);// Parent vector
    //dfs_recursive(adj,n,s,d,p);
    dfs_stack(adj,n,s,d,p);
    cout<<"Distance and Parent values :"<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<i<<" : "<<d[i]<<" "<<p[i]<<endl;
    }
}