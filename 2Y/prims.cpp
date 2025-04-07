#include <bits/stdc++.h>
using namespace std;

// Define 'int' as 'long long' for handling large integers
#define int long long

// Macro for fast input/output
#define tej ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

// Function to implement Prim's Algorithm
void primsAlgorithm(int n, vector<vector<pair<int, int>>> &adj) {
    // Priority queue to store the edges with their weights (min-heap)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Vector to store the minimum weight to reach each vertex
    vector<int> key(n, LLONG_MAX);

    // Vector to store the parent of each vertex in the MST
    vector<int> parent(n, -1);

    // Vector to check if a vertex is included in the MST
    vector<bool> inMST(n, false);

    int src = 0; // Starting node for the MST
    pq.push({0, src}); // Push the source node with weight 0
    key[src] = 0; // Set the key of the source node to 0

    // Loop until the priority queue is empty
    while (!pq.empty()) {
        // Extract the vertex with the smallest key value
        int u = pq.top().second;
        pq.pop();

        // Mark the vertex as included in the MST
        inMST[u] = true;

        // Traverse all adjacent vertices of the current vertex
        for (const auto &neighbor : adj[u]) {
            int v = neighbor.first; // Adjacent vertex
            int weight = neighbor.second; // Weight of the edge

            // If the vertex is not in the MST and the weight of the edge is smaller than the current key
            if (!inMST[v] && key[v] > weight) {
                key[v] = weight; // Update the key
                pq.push({key[v], v}); // Push the updated key into the priority queue
                parent[v] = u; // Update the parent of the vertex
            }
        }
    }

    // Calculate the total weight of the MST and print the edges
    int mstWeight = 0;
    cout << "Edges in the MST:\n";
    for (int i = 1; i < n; ++i) {
        // Print the edge and its weight
        cout << parent[i] << " - " << i << " : " << key[i] << "\n";
        mstWeight += key[i]; // Add the weight to the total MST weight
    }
    cout << "Weight of MST: " << mstWeight << "\n"; // Print the total weight of the MST
}

// Function to handle input and call Prim's Algorithm
void solve(int test) {
    int n, m; // Number of vertices and edges
    cin >> n >> m;

    // Adjacency list to store the graph
    vector<vector<pair<int, int>>> adj(n);

    // Input the edges of the graph
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight; // Input edge (u, v) with weight
        adj[u].push_back({v, weight}); // Add edge to adjacency list
        adj[v].push_back({u, weight}); // Add reverse edge for undirected graph
    }

    // Call Prim's Algorithm to find the MST
    primsAlgorithm(n, adj);
}

signed main() {
    tej; // Enable fast input/output
    int test = 1; // Number of test cases (currently set to 1)
    while (test--) {
        solve(test); // Solve each test case
    }
    return 0; // Exit the program
} 