#include <bits/stdc++.h>

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

using namespace std;

int non_bridge_edge_vertex(vvi &adj, int u, vi &low, vi &disc, vb &visited, int &time, int p){
    visited[u] = true;
    low[u] = disc[u] = ++time;

    int nonBridgeVertex = -1;

    for(int v : adj[u]){
        if(v == p){
            continue;
        }
        if(!visited[v]){
            non_bridge_edge_vertex(adj, v, low, disc, visited, time, u);
            low[u] = min(low[u], low[v]);
        }
        else{
            low[u] = min(low[u], disc[v]);
        }
    }

    // return the non-bridge edge vertex
    for(int i=0; i<adj[u].size(); i++){
        int v = adj[u][i];
        if(v == p){
            continue;
        }
        if(low[v] == disc[u]){
            return v;
        }
    }

    return nonBridgeVertex;
}

void removeEdge(vvi &adj, int u, int v) {
    auto it = find(adj[u].begin(), adj[u].end(), v);
    if (it != adj[u].end()) adj[u].erase(it);

    it = find(adj[v].begin(), adj[v].end(), u);
    if (it != adj[v].end()) adj[v].erase(it);
}

vector<int> findEulerTourUtil(vvi adj, int n, int e, int u){
    int time = 0;
    vi low(n+1, -1);
    vi disc(n+1, -1);
    vb visited(n+1, false);
    int count = 0;

    vector<int> ans;
    while(count < e){
        if(adj[u].size() == 1){
            count++;
            int v = adj[u][0];
            removeEdge(adj, u, v);
        }
        else{
            int v = non_bridge_edge_vertex(adj, u, low, disc, visited, time, -1);
            if (v == -1) v = adj[u][0];

            low.assign(n+1, -1);
            disc.assign(n+1, -1);
            visited.assign(n+1, false);
            count++;
            removeEdge(adj, u, v);
        }
        ans.push_back(u);
        u = v;
    }

    ans.push_back(u);
    return ans;
}

void print_euler_tour(vector<int> ans){
    for(int i=0; i<ans.size()-1; i++){
        cout<<ans[i]<<" => ";
    }
    cout<<ans[ans.size()-1];
    cout<<endl;
}

int findStartVertex(vvi adj, int n, bool directed){
    int startVertex = 1;
    unordered_map<int, int> indegreeCount, outDegreeCount;

    if(!directed){
        int oddDegreeCount = 0;
        for(int i=1; i<=n; i++){
            outDegreeCount[i] = adj[i].size();
            if(outDegreeCount[i] % 2 == 1){
                startVertex = i;
                oddDegreeCount++;
            }
        }

        if(oddDegreeCount > 2 || oddDegreeCount == 1){
            cout<<"Euler Tour is not possible"<<endl;
            return -1;
        }
    }
    else{
        int pos = 0, neg = 0;
        for(int i=1; i<=n; i++){
            for(int j=0; j<adj[i].size(); j++){
                outDegreeCount[i]++;
                indegreeCount[adj[i][j]]++;
            }
        }

        for(int i=1; i<=n; i++){
            if(indegreeCount[i] - outDegreeCount[i] == 1){
                pos++;
                startVertex = i;
            }
            else if(outDegreeCount[i] - indegreeCount[i] == 1){
                neg++;
            }
            else if(outDegreeCount[i] != indegreeCount[i]){
                cout<<"Euler Tour is not possible"<<endl;
                return -1;
            }
        }

        // Exactly one vertex should have outdegree - indegree = 1 and one vertex should have indegree - outdegree = 1
        if(pos! = neg || pos > 1){
            cout<<"Euler Tour is not possible"<<endl;
            return -1;
        }
    }
    return startVertex;
}

// Fleury's Algorithm
void findEulerTourFleury(vvi adj, int n, int e, bool directed){
    if(!adj.size()){
        cout<<"Empty Graph"<<endl;
        return;
    }
 
    int startVertex = findStartVertex(adj, n, directed);
    if(startVertex == -1){
        return;
    }

    vector<int> ans = findEulerTourUtil(adj, n, e, startVertex);
    print_euler_tour(ans);
}

// Hierholzer Algorithm
void findEulerTourHierholzer(vvi adj, int n, int e, bool directed){
    if(!adj.size()){
        cout<<"Empty Graph"<<endl;
        return;
    }

    unordered_map<int, int> edgeCount;

    for(int i=1; i<=n; i++){
        edgeCount[i] = adj[i].size();
    }

    int startVertex = findStartVertex(adj, n, directed);
    if(startVertex == -1){
        return;
    }

     // Stack to keep track of vertices
    stack<int> currPath;

    // Vector to store the final Euler Tour
    vector<int> circuit;

    currPath.push(startVertex);
    int currVertex = startVertex;

    while(!currPath.empty()){
        // If there's an edge from the current vertex
        if(edgeCount[currVertex]){
            currPath.push(currVertex);

            //Find the next vertex using the edge
            int nextVertex = adj[currVertex].back();

            // Remove the vertex and reduce the edge count
            edgeCount[currVertex]--;
            adj[currVertex].pop_back();

            currVertex = nextVertex;
        }
        // Backtrack to remaining path
        else{
            circuit.push_back(currVertex);
            currVertex = currPath.top();
            currPath.pop();
        }
    }

    vector<int> ans;
    for(int i=circuit.size()-1; i>=0; i--){
        ans.push_back(circuit[i]);
    }
    print_euler_tour(ans);
}

int main(){
    int n, s, e;
    cout<<"Enter the no of vertices and no of edges :"<<endl;
    cin>>n>>e;

    vvi adj(n+1);
    cout<<"Define edges :"<<endl;

    int param1,param2;
    for(int i=0;i<e;i++)
    {
        cin>>param1>>param2;
        adj[param1].push_back(param2);
        if(!directed) adj[param2].push_back(param1);
    }

    cout << "Is the graph directed? (0 for No, 1 for Yes): ";
    bool directed;
    cin >> directed;

    findEulerTourFleury(adj, n, e, directed); // Time Complexity: O(E^2) Using Tarjan's Bridge Algorithm
    // findEulerTourHierholzer(adj, n, e, directed); // Time Complexity: O(E) Using Hierholzer Algorithm

    return 0;
}