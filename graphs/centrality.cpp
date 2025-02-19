#include <bits/stdc++.h>

using namespace std;

vector<double> betweenness_centrality(vector<vector<int>> &graph){
    int n = graph.size();
    vector<double> centrality(n, 0.0);

    for(int s = 0; s < n; s++){
        // Data structures For BFS
        queue<int> q; // Keep the nodes to visit
        stack<int> st; // Keep the nodes in the order of the shortest path
        vector<int> dist(n, -1); // Distance from the source node
        vector<int> sigma(n, 0); // Number of shortest paths from s to v
        vector<double> delta(n, 0.0); // Dependency of s on v
        vector<vector<int>> pred(n); // Predecessors of each node

        dist[s] = 0;
        sigma[s] = 1;
        q.push(s);

        while(!q.empty()){
            int u = q.front();
            q.pop();
            st.push(u);

            for(int v : graph[u]){
                if(dist[v] == -1){ // If v is not visited
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }

                if(dist[v] == dist[u] + 1){
                    sigma[v] += sigma[u];
                    pred[v].push_back(u);
                }
            }
        }

        vector<double> delta(n, 0.0);
        while(!q.empty()){
            int u = q.front();
            q.pop();

            for(int v : pred[u]){
                delta[v] += (sigma[v] / sigma[u]) * (1 + delta[u]); // Fraction of shortest paths from s to v that pass through u scaled by the dependency of s on u
            }

            if(u != s){
                centrality[u] += delta[u];
            }
        }
    }

    return centrality;
}

int main(){
    int n = 6;
    vector<vector<int>> graph(n);

    graph[0] = {1, 2};
    graph[1] = {0, 2, 3};
    graph[2] = {0, 1, 4};
    graph[3] = {1, 4, 5};
    graph[4] = {2, 3, 5};
    graph[5] = {3, 4};

    vector<double> centrality = betweenness_centrality(graph);
    return 0;
}