#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF LLONG_MAX

// Function to implement Bellman-Ford Algorithm
void bellmanFord(int n, int m, int src, vector<tuple<int, int, int>> &edges) {
    // Distance vector to store the shortest distance from the source to each vertex
    vector<int> dist(n, INF);
    dist[src] = 0; // Distance to the source is 0

    // Relax all edges (n-1) times
    for (int i = 1; i <= n - 1; ++i) {
        for (auto &[u, v, w] : edges) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative weight cycles
    for (auto &[u, v, w] : edges) {
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "Graph contains a negative weight cycle.\n";
            return;
        }
    }

    // Print the shortest distances
    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << "\t" << (dist[i] == INF ? "INF" : to_string(dist[i])) << "\n";
    }
}

signed main() {
    int n, m; // Number of vertices and edges
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    vector<tuple<int, int, int>> edges; // To store edges as (u, v, weight)

    cout << "Enter the edges (u v weight):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u - 1, v - 1, w}); // Convert to 0-based indexing
    }

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    bellmanFord(n, m, src - 1, edges); // Convert source to 0-based indexing

    return 0;
}