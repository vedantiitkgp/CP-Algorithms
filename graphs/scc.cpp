// https://cp-algorithms.com/graph/strongly-connected-components.html
// https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm

/* Algorithms -
- Konsaraju's Algorithm
- Tarjan's Algorithm
*/

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
typedef stack<int> st;

void dfs(vvi adj,int u,vi &result,vb &visited)
{
    visited[u] = true;
    for(int v:adj[u])
    {
        if(!visited[v]) dfs(adj,v,result,visited);
    }
    result.push_back(u);
}

vi topological_sort(vvi adj,int n)
{
    vb visited(n+1,false);
    vi result;
    for(int i=1;i<=n;i++)
    {
        if(!visited[i]) dfs(adj,i,result,visited);
    }
    reverse(result.begin(),result.end());
    return result;
}

vvi transpose(vvi adj,int n)
{
    vvi adjT(n+1);
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<adj[i].size();j++)
        {
            adjT[adj[i][j]].push_back(i);
        }
    }
    return adjT;
}

void dfs_transpose(vvi adj,int u,vi &temp,vb &visited)
{
    visited[u] = true;
    temp.push_back(u);
    for(int v: adj[u])
    {
        if(!visited[v]) dfs_transpose(adj,v,temp,visited);
    }
}

void print_scc(vvi ans)
{
    for(int i=0;i<ans.size();i++)
    {
        cout<<"SCC "<<i+1<<": ";
        for(int j=0;j<ans[i].size();j++)
        {
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
}

// Kosaraju's Algorithm
void find_kosaraju_scc(vvi adj,int n)
{
    vi top_sort = topological_sort(adj,n);
    vvi adjT = transpose(adj,n);
    vb visited(n+1,false);
    vvi ans;
    for(int i=0;i<n;i++)
    {
        vi temp;
        if(!visited[top_sort[i]]) dfs_transpose(adjT,top_sort[i],temp,visited);
        if(temp.size()>0)ans.push_back(temp);
    }
    print_scc(ans);
}


void find_strongly_connected(vvi &adj, int n, int node,  vi &index, vi &low_index,  vb &on_stack, st &node_stack, int &current_index, vvi &ans){
    index[node] = current_index;
    low_index[node] = current_index;
    current_index++;
    node_stack.push(node);
    on_stack[node] = true;

    for(auto neighbor : adj[node]){
        if(index[neighbor] == -1 ){
            find_strongly_connected(adj, n, neighbor, index, low_index, on_stack, node_stack, current_index, ans);
            low_index[node] = min(low_index[node], low_index[neighbor]);
        }
        else if(on_stack[neighbor]){
            low_index[node] = min(low_index[node], index[neighbor]);
        }
    }

    if(low_index[node] == index[node]){
        vi temp;
        do{
            int w = node_stack.top();
            node_stack.pop();
            on_stack[w] = false;
            temp.push_back(w);
        }
        while(w != node);

        if(!temp.empty()) ans.push_back(temp);
    }
}

// Tarjan's Algorithm
void find_tarjan_scc(vvi adj, int n){
    vi index(n+1, -1);
    vi low_index(n+1, -1);
    vb on_stack(n+1, false);
    st node_stack;
    vvi ans;
    int current_index = 1;

    for(int i=1; i<=n; i++){
        if(index[i] == -1){
            find_strongly_connected(adj, n, i, index, low_index, on_stack, node_stack, current_index, ans);
        }
    }
    print_scc(ans);
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
    find_kosaraju_scc(adj,n);
    // find_tarjan_scc(adj, n);
   return 0;
}