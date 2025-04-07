#include <bits/stdc++.h>
using namespace std;

#define int long long
#define tej ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define mod 1000000007

class FastInput {
public:
    FastInput() {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
    }

    int nextInt() {
        int x;
        cin >> x;
        return x;
    }

    long long nextLong() {
        long long x;
        cin >> x;
        return x;
    }
};

FastInput in;

void dijkstra(int src, vector<vector<pair<int, int>>>& adj, vector<int>& dist, vector<int>& parent) {
    int n = adj.size();
    dist.assign(n, LLONG_MAX);
    parent.assign(n, -1);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight; 
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void printPath(int v, vector<int>& parent) {
    if (v == -1) return;
    printPath(parent[v], parent);
    cout << v + 1 << " "; // Convert to 1-based indexing for output
}

void solve(int test) {
    int n = in.nextInt(); // Number of vertices
    int m = in.nextInt(); // Number of edges
    vector<vector<pair<int, int>>> adj(n);

    for (int i = 0; i < m; ++i) {
        int u = in.nextInt() - 1; // Convert to 0-based indexing
        int v = in.nextInt() - 1; // Convert to 0-based indexing
        int w = in.nextInt();
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int src = in.nextInt() - 1; // Convert to 0-based indexing

    vector<int> dist, parent;
    dijkstra(src, adj, dist, parent);

    for (int i = 0; i < n; ++i) {
        if (i != src) {
            cout << src + 1 << " - " << i + 1 << " | Dist: " << dist[i] << " | Path: ";
            printPath(i, parent);
            cout << endl;
        }
    }
}

signed main() {
    tej;
    int test = 1;
    while (test--) {
        solve(test);
    }
    return 0;
}