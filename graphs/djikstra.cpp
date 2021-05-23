// https://cp-algorithms.com/graph/dijkstra.html

#include<bits/stdc++.h>
#define INF 100000000

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int,ll> pil;
typedef pair<string, string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<pil> vil;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef vector<vii> vvii;
typedef vector<vil> vvil;

void print_djikstra(vl dist,vi prev,int n,int s)
{
    cout<<"Source vertex : "<<s<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<i<<" : "<<dist[i]<<endl;
    }
    cout<<"Shortest_paths"<<endl;
    for(int i=1;i<=n;i++)
    {
        vi temp1;
        temp1.push_back(i);
        int temp2 = prev[i];
        while(temp2!=-1)
        {
            temp1.push_back(temp2);
            temp2 = prev[temp2];   
        }
        reverse(temp1.begin(),temp1.end());
        cout<<"Path "<<i<<" : ";
        for(int j=0;j<temp1.size();j++)
        {
            cout<<temp1[j]<<" ";
        }
        cout<<endl;
    }
}


//Djikstra on sparse graphs (m is lot less than n^2)
void djikstra_sparse(vvil adj,int s,int n)
{
    vl dist(n+1,INF);
    vb visited(n+1,false);
    vi prev(n+1,-1);
    dist[s] = 0;
    prev[s] = -1;
    priority_queue<pil,vector<pil>,greater<pil>> q;
    q.push({0,s});
    while(!q.empty())
    {
        int v = q.top().second;
        ll d_v = q.top().first;
        q.pop();
        if(d_v!=dist[v]) continue;
        for(auto edge: adj[v])
        {
            int to = edge.first;
            ll len = edge.second;
            if(dist[v]+len<dist[to])
            {
                dist[to] = dist[v] + len;
                prev[to] = v;
                q.push({dist[to],to});
            }
        }
    }
    print_djikstra(dist,prev,n,s);
}

// Djikstra on Dense Graphs(m is almost equal to n^2) - Complexity(O(n^2+m))
int find_min(vl dist,vb &visited,int n)
{
    ll min_value = INF;
    int index;
    for(int i=1;i<=n;i++)
    {
        if(dist[i]<min_value&&!visited[i]) 
        {
            min_value = dist[i];
            index = i;
        }
    }
    return index;
}

//Single source shortest path problem
void djikstra(vvil adj,int s,int n)
{
    vb visited(n+1,false);
    vl dist(n+1,INF);
    vi prev(n+1,-1);
    dist[s] = 0;
    prev[s] = -1;
    for(int i=0;i<n;i++)
    {
        int v = find_min(dist,visited,n);
        visited[v] = true;
        if(dist[v]==INF)continue;
        for(pil edge:adj[v])
        {
            if(dist[edge.first]>dist[v]+edge.second)
            {
                dist[edge.first] = dist[v] + edge.second;
                prev[edge.first] = v;
            }
        }
    }
    print_djikstra(dist,prev,n,s);
}

int main()
{
    int n,s,e;
    cout<<"Enter the no of vertices and no of edges :"<<endl;
    cin>>n>>e;
    cout<<"Enter the source vertex :"<<endl;
    cin>>s;
    vvil adj(n+1);
    cout<<"Define edges :"<<endl;
    int param1,param2;
    ll param3;
    for(int i=0;i<e;i++)
    {
        cin>>param1>>param2>>param3;
        adj[param1].push_back({param2,param3});
    }
    cout<<endl;
    djikstra(adj,s,n);
    //djikstra_sparse(adj,s,n);
    return 0;
}