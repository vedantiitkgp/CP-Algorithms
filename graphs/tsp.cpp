#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;

int exactTSPUtil(int mask, int curr, int n, vector<vii> &adj, vector<vector<int>> &dp) {   
    if (mask == (1 << n) - 1) {
        dp[mask][curr] = INT_MAX;
        // Return cost to reach back to starting node if edge exists
        for (auto &[next, cost] : adj[curr]) {
            if (next == 0) dp[mask][curr] = cost;
        }
        return dp[mask][curr]; // No valid path back
    }

    if (dp[mask][curr] != -1) {
        return dp[mask][curr];
    }
    

    dp[mask][curr] = INT_MAX;

    // Iterate over all the neighbors of the current node
    for (auto &[next, cost] : adj[curr]) {   
        if ((mask & (1 << next)) == 0) { // If node is not visited
            int nextCost = exactTSPUtil(mask | (1 << next), next, n, adj, dp);
            if (nextCost != INT_MAX && nextCost + cost < dp[mask][curr]) {
                dp[mask][curr] = nextCost + cost;
                cout<<mask<<" "<<curr<<" "<<dp[mask][curr]<<endl;
            }
        }
    }
    return dp[mask][curr];
}

void exactTSP(int n, vector<vii> &adj) {
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));
    int cost = exactTSPUtil(1, 0, n, adj, dp);
    cout << "Cost of the TSP tour is: " << cost << endl;
    if (cost == INT_MAX) {
        cout << "No valid TSP tour exists.\n";
        return;
    }
    
    // Reconstruct the path
    vector<int> path;
    int curr = 0;
    int mask = 1 << curr;
    path.push_back(curr);

    int remaining = n - 1;
    while (remaining > 0) {
        for (auto &[next, cost_edge] : adj[curr]) {
            if (!(mask & (1 << next))) {
                int new_mask = mask | (1 << next);
                if (dp[mask][curr] == dp[new_mask][next] + cost_edge) {
                    path.push_back(next);
                    curr = next;
                    mask = new_mask;
                    remaining--;
                    break;
                }
            }
        }
    }

    // Add the return to the starting city
    path.push_back(0);

    cout << "The tour is: ";
    
    cout << "The tour is: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << "->";
        }
    }
    cout << endl;
}

int main() {
    int n = 4, e = 6;
    
    cout << "Enter the number of vertices and number of edges: ";
    cin >> n >> e;

    if (n <= 1 || e < n) {
        cout << "Invalid input: The graph must have at least one vertex and enough edges to form a cycle.\n";
        return 0;
    }

    vector<vii> adj(n);
    cout << "Define edges (u v weight):" << endl;
    for (int i = 0; i < e; i++) {   
        int u, v, weight;
        cin >> u >> v >> weight;
        if (u < 0 || v < 0 || u >= n || v >= n || weight <= 0) {
            cout << "Invalid edge input.\n";
            return 0;
        }
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    exactTSP(n, adj);
    return 0;
}