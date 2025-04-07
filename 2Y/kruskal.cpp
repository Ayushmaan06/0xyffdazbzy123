#include <bits/stdc++.h>
using namespace std;

#define int long long
#define tej ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

class Edge {
public:
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

class DisjointSet {
public:
    vector<int> parent, rank;
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

void solve(int test) {
    int n, m;
    // cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;
    vector<Edge> edges;
    // cout << "Enter the edges (u v weight):\n";
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges.push_back(Edge(u, v, weight));
    }

    sort(edges.begin(), edges.end(), compare);

    DisjointSet ds(n);
    int mstWeight = 0;
    vector<Edge> mst;

    for (Edge edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            ds.unionSets(edge.u, edge.v);
            mstWeight += edge.weight;
            mst.push_back(edge);
        }
    }

    cout << "Weight of MST: " << mstWeight << "\n";
    cout << "Edges in the MST:\n";
    for (Edge edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << "\n";
    }
}

signed main() {
    tej;
    solve(0);
    return 0;
}