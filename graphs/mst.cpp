/*
  Minimum Spannning Trees
   -- Kruksal Algorithm (1956)
   -- Prim's or Jarnik Algorithm (1930)
   -- Boruvka or Sollin's Algorithm (1926)
   
   [Faster Algorithms
    -- Trans Dichotomous Algorithms (1994)
    -- Randomized Linear Time Algorithm (1995) - https://cs.brown.edu/research/pubs/pdfs/1995/Karger-1995-RLT.pdf
    -- Inverse Ackermann Time Compelxity MST (2000) - https://www.cs.princeton.edu/~chazelle/pubs/mst.pdf
    ]

   Time Complexity - O(nlogn)
*/


// https://cp-algorithms.com/graph/mst_kruskal.html
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/

#include <bits/stdc++.h>
#define INF 1000000

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
    int u, v, weight;
    edge(int u, int v) : u(u), v(v), weight(INF) {};
    edge(int u, int v, int weight) : u(u), v(v), weight(weight) {};
};

bool compareEdge(edge e1, edge e2)
{
    return (e1.weight < e2.weight);
}

void make_set(int v, vi &parent, vi &rank)
{
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v, vi &parent)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v], parent);
}

void union_sets(int u, int v, vi &parent, vi &rank)
{
    int uroot = find_set(u, parent);
    int vroot = find_set(v, parent);
   
    if(rank[uroot] < rank[vroot]){
        parent[uroot] = vroot; 
    }
    else if(rank[uroot] > rank[vroot]){
        parent[vroot] = uroot;
    }
    else{
        parent[vroot] = uroot;
        rank[uroot]++;
    }
}

// Kruskal algorithm with union compression
vector<edge> kruskal_union_algo(vector<edge> edges, int n, int &cost)
{
    vi parent(n + 1);
    vi rank(n + 1);

    for (int i = 1; i <= n; i++)
    {
        make_set(i, parent, rank);
    }
    vector<edge> mstEdges;
    sort(edges.begin(), edges.end(), compareEdge);
    for (edge e : edges)
    {
        if (find_set(e.u, parent) != find_set(e.v, parent))
        {
            cost += e.weight;
            mstEdges.push_back(e);
            union_sets(e.u, e.v, parent, rank);
        }
    }
    return mstEdges;
}

class CustomViComparator {
    public:
    bool operator()(vi below, vi above){
        return below[0] > above[0];
    }
};

// Prim's Algo with Priority queue
vector<edge> prim_algo(vector<vector<pii>> &adj, int n, int& cost)
{
    vb visited(n+1, false);
    vector<edge> mstEdges;
    priority_queue <vi, vvi, CustomViComparator> pq;

    pq.push({0,0, -1});

    while(!pq.empty()){
        vi current = pq.top();
        pq.pop();
        int wt = current[0];
        int node = current[1];
        int parent = current[2];

        if(visited[node]){
            continue;
        }

        cost += wt;
        visited[node] = true;
        if(parent != -1){
            mstEdges.push_back(edge(node, parent, wt));
        }
    
        for(pii neighbor : adj[node]){
            if(!visited[neighbor.first]){
                pq.push({neighbor.second, neighbor.first, node});
            }
        }
    }

    return mstEdges;
}

vector<vector<pii> > createAdjacencyList(vector<edge> edges, int n)
{
    vector<vector<pii> > adj(n+1);
    for (edge e1 : edges)
    {
        adj[e1.u].push_back({e1.v, e1.weight});
        adj[e1.v].push_back({e1.u, e1.weight});
    }
    return adj;
}

// Boruvka's Algorithm
vector<edge> boruvka_algo(vector<edge> edges, int n, int &cost){
    vi parent(n + 1);
    vi rank(n + 1);

    for (int i = 1; i <= n; i++)
    {
        make_set(i, parent, rank);
    }

    int numTrees = n;
    int MSTWeight = 0;
    vvi cheapest(n+1, vector<int>(3, -1));
    vector<edge> mstEdges;

    while(numTrees > 1){
        // Traverse through all edges
        for(int i=0; i<edges.size();i++){
            int u = edges[i].u;
            int v = edges[i].v;
            int weight = edges[i].weight;

            int set1 = find_set(u, parent);
            int set2 = find_set(v, parent);

            if(set1 != set2){
                if(cheapest[set1][2] == -1 || cheapest[set1][2] > weight){
                    cheapest[set1][2] = {u, v, weight};
                }

                if(cheapest[set2][2] == -1 || cheapest[set2][2] > weight){
                    cheapest[set2][2] = {u, v, weight};
                }
            }
        }

        //Pick Cheapest edge for each set
        for(int node=1; node <= n; node++){
            if(cheapest[node][2] != -1){
                int u = cheapest[node][0];
                int v = cheapest[node][1];
                int weight = cheapest[node][2];
                
                int set1 = find_set(u, parent);
                int set2 = find_set(v, parent);

                if(set1 != set2){
                    cost += weight;
                    union_sets(set1, set2, parent, rank);
                    mstEdges.push_back(edge(u, v, weight));
                    numTrees--;
                }

            }
        }

        //reset cheapest array
        for(int node=1; node<=n; node++){
            cheapest[node][2] = -1;
        }
    }
    return mstEdges;
}

int main()
{
    int n, e;
    cout << "Enter the no of vertices and no of edges :" << endl;
    cin >> n >> e;
    cout << "Define edges :" << endl;
    vector<edge> edges;
    for (int i = 0; i < e; i++)
    {   
        int u, v, weight;
        cin >> u >> v >> weight;
        edges.push_back(edge(u, v, weight));
    }
    int cost = 0;
    vector<vector<pii> >adj = createAdjacencyList(edges, n);
    // vector<edge> result = kruskal_union_algo(edges, n, cost);
    // vector<edge> result = boruvka_algo(edges, n, cost);
    vector<edge> result = prim_algo(adj, n, cost);
    cout << endl;
    cout << "Cost : " << cost << endl;
    cout << endl;
    cout << "Edges in MST :" << endl;
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i].u << " " << result[i].v << endl;
    }
    return 0;
}