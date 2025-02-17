/*
    Implementation of Apprixmate TSP using Prim MST
    Time Complexity - O(nlogn) -- 2 Approximation

    Implementation of Apprixmate TSP using Christofides Algorithm
    Time Complexity - O(n^2) -- 1.5 Approximation
*/

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

    pq.push({0,1, -1});

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
            if(neighbor.first == parent){
                continue;
            }

            if(!visited[neighbor.first]){
                pq.push({neighbor.second, neighbor.first, node});
            }
        }
    }
    return mstEdges;
}

// Greedy method to find minimum matching
vector<edge> findMinimumMatching(vector<vector<pii>> &adj, vector<int> &oddNodes) {
    vector<edge> matchingEdges;
    if (oddNodes.empty()) return matchingEdges;

    vector<edge> candidateEdges;
    for (int i = 0; i < oddNodes.size(); ++i) {
        int u = oddNodes[i];
        for (int j = i + 1; j < oddNodes.size(); ++j) {
            int v = oddNodes[j];
            for (const pii &neighbor : adj[u]) {
                if (neighbor.first == v) {
                    candidateEdges.emplace_back(u, v, neighbor.second);
                    break;
                }
            }
        }
    }

    sort(candidateEdges.begin(), candidateEdges.end(), compareEdge);

    unordered_set<int> matched;
    for (const edge &e : candidateEdges) {
        if (matched.find(e.u) == matched.end() && matched.find(e.v) == matched.end()) {
            matchingEdges.push_back(e);
            matched.insert(e.u);
            matched.insert(e.v);
        }
        if (matched.size() == oddNodes.size()) break;
    }

    return matchingEdges;
}

// Eulerian Tour Assumes Graph distances always follow triangle inequality
void eulerianCircuit(vector<vector<pii>> &adj, int n, int node, vector<int> &tour, vb &visited, int parent)
{
    visited[node] = true;
    tour.push_back(node);
    for(pii neighbor : adj[node]){
        if(neighbor.first == parent){
            continue;
        }
    
        if(!visited[neighbor.first]){
            eulerianCircuit(adj, n, neighbor.first, tour, visited, node);
        }
    }
}

vector<edge> approximateTSP_Christofides(vector<vector<pii>> &adj, int n) {
    int mstCost = 0;
    vector<edge> mstEdges = prim_algo(adj, n, mstCost);
    vector<vector<pii>> mstAdj(n + 1);
    vi degrees(n + 1, 0);
    for (const edge &e : mstEdges) {
        mstAdj[e.u].emplace_back(e.v, e.weight);
        mstAdj[e.v].emplace_back(e.u, e.weight);
        degrees[e.u]++;
        degrees[e.v]++;
    }

    vector<int> oddNodes;
    for (int i = 1; i <= n; ++i) {
        if (degrees[i] % 2 != 0) {
            oddNodes.push_back(i);
        }
    }

    vector<edge> matchingEdges = findMinimumMatching(adj, oddNodes);
    vector<vector<pii>> multigraphAdj = mstAdj;
    for (const edge &e : matchingEdges) {
        multigraphAdj[e.u].emplace_back(e.v, e.weight);
        multigraphAdj[e.v].emplace_back(e.u, e.weight);
    }

    vector<int> tour;
    vb visited(n + 1, false);
    eulerianCircuit(multigraphAdj, n, 1, tour ,visited, -1);
    tour.push_back(1);

    vector<edge> tourPath;

    for (int i = 0; i < tour.size() - 1; i++) {
        int u = tour[i];
        int v = tour[i + 1];
        int weight = 0;

        for (pii neighbor : adj[u]) {
            if (neighbor.first == v) {
                weight = neighbor.second;
                break;
            }
        }

        tourPath.push_back(edge(u, v, weight));
    }
    return tourPath;
}

vector<edge> approximateTSP_MST(vector<vector<pii>> &adj, int n)
{
    int mstCost = 0;
    vector<edge> mstEdges = prim_algo(adj, n, mstCost);
    vb visited(n+1, false);

    vector<vector<pii>> mstAdj(n+1);
    for(edge e : mstEdges){
        mstAdj[e.u].push_back({e.v, e.weight});
        mstAdj[e.v].push_back({e.u, e.weight});
    }
    
    vector<int> tour;
    eulerianCircuit(mstAdj, n, 1, tour ,visited, -1);
    tour.push_back(1);
    vector<edge> tourPath;

    for (int i = 0; i < tour.size() - 1; i++) {
        int u = tour[i];
        int v = tour[i + 1];
        int weight = 0;

        for (pii neighbor : adj[u]) {
            if (neighbor.first == v) {
                weight = neighbor.second;
                break;
            }
        }

        tourPath.push_back(edge(u, v, weight));
    }
    return tourPath;
}

int tourCost(vector<edge> &tourPath)
{
    int cost = 0;
    for(edge e : tourPath){
        cost += e.weight;
    }
    return cost;
}

void handleViolations(vector<vector<pii>> &adj, int n) {
    cout << "Do you want to Check for triangle equality violations? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'n' || choice == 'N') {
        return;
    }

    vector<tuple<int, int, int>> violationTriplets; // Vector to store unique triplets (u, v, w)

    // Check triangle inequality for each triplet of nodes (u, v, w)
    for (int u = 1; u <= n; u++) {
        for (auto &pair1 : adj[u]) {
            int v = pair1.first;
            int weight_uv = pair1.second;

            for (auto &pair2 : adj[v]) {
                int w = pair2.first;
                int weight_vw = pair2.second;

                // Check if there is an edge u -> w and check the triangle inequality
                for (auto &pair3 : adj[u]) {
                    if (pair3.first == w) {
                        int weight_uw = pair3.second;
                        if (weight_uv + weight_vw < weight_uw) {
                            // Prevent storing (u, v, w) and (w, v, u)
                            if (u < w) {
                                violationTriplets.push_back({u, v, w});
                            }
                        }
                    }
                }
            }
        }
    }

    // Notify the user about violation triplets
    if (!violationTriplets.empty()) {
        cout << "Triangle Inequality Violating Triplets (u, v, w):" << endl;
        for (const auto &triplet : violationTriplets) {
            int u = get<0>(triplet);
            int v = get<1>(triplet);
            int w = get<2>(triplet);
            cout << "d(" << u << ", " << v << ") + d(" << v << ", " << w << ") < d(" << u << ", " << w << ")" << endl;
        }
    } else {
        cout << "No Violations Found" << endl;
    }
}

vector<vector<pii>> createAdjacencyList(vector<edge> &edges, int n) {
    vector<vector<pii>> adj(n + 1);
    
    for (edge e : edges) {
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }
    
    // Sort each adjacency list based on the weight of the edges
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end(), [](const pii &a, const pii &b) {
            return a.second < b.second;
        });
    }
    
    handleViolations(adj, n);
    return adj;
}


int main(){
    int n, e;
    cout<<">>> Current Graph is Undirected, Dense and TSP Tour Exists <<< "<<endl;
    cout<<endl;
    cout << "Enter the no of vertices and no of edges : (n, e)" << endl;
    cin >> n >> e;
    cout << "Define edges : (u, v, weight)" << endl;
    vector<edge> edges;
    for (int i = 0; i < e; i++)
    {   
        int u, v, weight;
        cin >> u >> v >> weight;
        edges.push_back(edge(u, v, weight));
    }
    
    vector<vector<pii> >adj = createAdjacencyList(edges, n);
    vector<edge> tspTour = approximateTSP_MST(adj, n);
    // vector<edge> tspTour = approximateTSP_Christofides(adj, n);

    cout<<endl;
    cout<<"-- TSP Tour --"<<endl;
    for (int i = 0; i < tspTour.size(); i++)
    {
        if (i == 0) {
            cout << tspTour[i].u << " -> "<< tspTour[i].v;
        } else {
            cout << " -> "<<tspTour[i].v;
        }
    }
    cout<<endl;

    int tspTourCost = tourCost(tspTour);
    cout<<"Cost of Approximate TSP : "<<tspTourCost<<endl;
    return 0;
}