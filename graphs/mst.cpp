// https://cp-algorithms.com/graph/mst_kruskal.html
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/

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

struct edge
{
    int u,v,weight;
};

bool compareEdge(edge e1,edge e2)
{
    return (e1.weight<e2.weight);
}

void make_set(int v,vi &parent)
{
    parent[v] = v;
}

int find_set(int v, vi &parent)
{
    if(v==parent[v]) return v;
    return parent[v] = find_set(parent[v],parent);
}

void union_sets(int u,int v,vi &parent)
{
    u = find_set(u,parent);
    v = find_set(v,parent);
    if(u!=v)
    {
        parent[v] = u;
    }
}


// Kruskal algorithm with union compression
vector<edge> kruskal_union_algo(vector<edge> edges,int n,int &cost)
{
    vi parent(n+1);
    for(int i=1;i<=n;i++)
    {
        make_set(i,parent);
    }
    vector<edge> result;
    sort(edges.begin(),edges.end(),compareEdge);
    for(edge e :edges)
    {
        if(find_set(e.u,parent)!=find_set(e.v,parent))
        {
            cost+=e.weight;
            result.push_back(e);
            union_sets(e.u,e.v,parent);
        }
    }
    return result;
}

// Plain Kruskal algorithm
vector<edge> kruskal_algo(vector<edge> edges,int n,int &cost)
{
    vi tree_id(n+1);
    int old_id,new_id;
    for(int i=1;i<=n;i++)
    {
        tree_id[i] = i;
    }
    vector<edge> result;
    sort(edges.begin(),edges.end(),compareEdge);
    for(edge e1 :edges)
    {
        if(tree_id[e1.u]!=tree_id[e1.v])
        {
            cost+= e1.weight;
            result.push_back(e1);
            old_id = tree_id[e1.u];
            new_id = tree_id[e1.v];
            for(int i=1;i<=n;i++)
            {
                if(tree_id[i]==old_id) tree_id[i] = new_id;
            }
        }
    }
    return result;
}

int main()
{
    int n,e;
    cout<<"Enter the no of vertices and no of edges :"<<endl;
    cin>>n>>e;
    cout<<"Define edges :"<<endl;
    int param1,param2;
    vector<edge> edges;
    edge e1;
    for(int i=0;i<e;i++)
    {
        cin>>e1.u>>e1.v>>e1.weight;
        edges.push_back(e1);
    }
    int cost=0;
    vector<edge> result = kruskal_union_algo(edges,n,cost);
    cout<<endl;
    cout<<"Cost : "<<cost<<endl;
    cout<<endl;
    cout<<"Edges in MST :"<<endl;
    for(int i=0;i<result.size();i++)
    {
        cout<<result[i].u<<" "<<result[i].v<<endl;
    }
    return 0;
}