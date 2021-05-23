// https://cp-algorithms.com/graph/breadth-first-search.html
// https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
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

void bfs(vvi adj,int n,int s,vi &d,vi &p)
{
    vector<bool> visited(n+1,false); 
    queue<int> q;
    q.push(s);
    visited[s] = true;
    p[s] = -1;
    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        for(int u: adj[v])
        {
            if(!visited[u])
            {
                visited[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
                p[u] = v;
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
    bfs(adj,n,s,d,p);
    cout<<"Distance and Parent values :"<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<i<<" : "<<d[i]<<" "<<p[i]<<endl;
    }
    return 0;
}

//Applications :
// 1. Shortest path finding in a graph
// 2. Find all connected components
// 3. Soloution to problem with least no of moves ex - jug problem
// 4. Shortest path between any two vertices 
// 5. 0-1 BFS(Special case of djikstra where weight of edges is 0,1)(Further can be extended to k via Dial's Algorithm)
