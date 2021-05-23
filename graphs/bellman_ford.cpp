//https://cp-algorithms.com/graph/bellman_ford.html

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

struct edge
{
    int a,b;
    ll cost;
};

void cycle_find_bellman_ford(vi prev,int n,int s,int x)
{
    int y = x;
    for (int i=0; i<n; ++i)
        y = prev[y];

    vi path;
    for (int cur=y; ; cur=prev[cur])
    {
        path.push_back (cur);
        if (cur == y && path.size() > 1)
            break;
    }
    reverse (path.begin(), path.end());
    for (int i=0; i<path.size();i++)
            cout << path[i] << " ";
    cout<<endl;
}

void print_bellman_ford(vl dist,vi prev,int n,int s)
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

// Shortest path from single source with negative weights
void bellman_ford(vector<edge> edges,int n,int e,int s)
{
    vl dist(n+1,INF);
    vi prev(n+1,-1);
    prev[s] = -1;
    dist[s] =0;
    int x;
    for(int i=0;i<n-1;i++) // Atleast n-1 iterations and nth iteration for finding a cycle
    {
        bool any = false;
        x = -1;
        for(int j=0;j<e;j++)
        {
            if(dist[edges[j].a]<INF)
            {
                if(dist[edges[j].a]+edges[j].cost<dist[edges[j].b])
                {
                    dist[edges[j].b] = dist[edges[j].a] + edges[j].cost;
                    prev[edges[j].b] = edges[j].a;
                    any = true;
                    x = edges[j].b;
                }
            }
        }
        if(!any) break;
    }
    if(x==-1) cout<<"No Cycle Present"<<endl;
    else{
        cout<<"Cycle Present :";
        cycle_find_bellman_ford(prev,n,s,x);
    }
    print_bellman_ford(dist,prev,n,s);
}

int main()
{
    int n,s,e;
    cout<<"Enter the no of vertices and no of edges :"<<endl;
    cin>>n>>e;
    cout<<"Enter the source vertex :"<<endl;
    cin>>s;
    vvil adj(n+1);
    vector<edge> edges;
    cout<<"Define edges :"<<endl;
    int param1,param2;
    ll param3;
    for(int i=0;i<e;i++)
    {
        cin>>param1>>param2>>param3;
        adj[param1].push_back({param2,param3});
        edge e1;
        e1.a = param1;
        e1.b = param2;
        e1.cost = param3;
        edges.push_back(e1);
    }
    cout<<endl;
    bellman_ford(edges,n,e,s);
    return 0;
}

// SFPA Algorithm (To be tested)