/*

Find all maximal cliques in an undirected graph using the Bron–Kerbosch algorithm with pivoting.
Time - O(3^(n/3)), where n is the number of vertices in the graph

*/

#include <bits/stdc++.h>

using namespace std;

// Graph representation using an adjacency list
unordered_map<int, unordered_set<int>> graph;

// Function to add an edge to the graph
void addEdge(int u, int v) {
    graph[u].insert(v);
    graph[v].insert(u); // Since the graph is undirected
}

// Bron–Kerbosch with pivoting
void bronKerboschPivot(unordered_set<int>& R, unordered_set<int>& P, unordered_set<int>& X) {
    if (P.empty() && X.empty()) {
        // Output a maximal clique
        cout << "{ ";
        for (int v : R) cout << v << " ";
        cout << "}" << endl;
        return;
    }

    // Choose pivot: the vertex with the maximum number of neighbors or smallest non neighbors in P
    int pivot = *P.begin();
    int maxNbrs = 0;
    for (int v : P) {
        int nbrs = 0;
        for (int u : P) {
            if (graph[v].count(u)) nbrs++;
        }
        if (nbrs > maxNbrs) {
            maxNbrs = nbrs;
            pivot = v;
        }
    }

    // Iterate over all non-neighbors and self of pivot in P
    unordered_set<int> nonNeighbors;
    for (int v : P) {
        if (graph[pivot].find(v) == graph[pivot].end()) {
            nonNeighbors.insert(v);
        }
    }

    for (int v : nonNeighbors) {
        unordered_set<int> newR = R, newP, newX;
        newR.insert(v);
        
        for (int u : P) {
            if (graph[v].count(u)) newP.insert(u);
        }
        for (int u : X) {
            if (graph[v].count(u)) newX.insert(u);
        }

        bronKerboschPivot(newR, newP, newX);
        
        P.erase(v);
        X.insert(v);
    }
}

// Driver function
int main() {
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
    }

    unordered_set<int> P;
    for (int i = 0; i < vertices; i++) {
        P.insert(i); // Assuming vertices are labeled from 0 to vertices-1
    }

    unordered_set<int> R, X;

    cout << "Maximal cliques found:\n";
    bronKerboschPivot(R, P, X);

    return 0;
}