#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n + 1);
		vector<int> dist(n + 1, INT_MAX);
		vector<int> visited(n + 1, false);
		priority_queue< pair<int,int>, vector< pair<int,int> >, greater<pair<int,int>> > pq;

		// create the adjency array + each cost
		for (int i = 0; i < times.size(); ++i)
		{
			adj[times[i][0]].push_back({times[i][1], times[i][2]});
		}

		// dijkstra

		dist[k] = 0;
		pq.emplace(0, k);
		while (!pq.empty())
		{
			int curr = pq.top().second;
			pq.pop();
			if (visited[curr])
				continue;
			visited[curr] = true;
			for (int i = 0; i < adj[curr].size(); ++i)
			{
				if (dist[adj[curr][i].first] > dist[curr] + adj[curr][i].second)
					dist[adj[curr][i].first] = dist[curr] + adj[curr][i].second;
				pq.emplace(dist[adj[curr][i].first], adj[curr][i].first);
			}
		}

		int max = 0;
		for (int i = 1; i < dist.size(); ++i)
		{
			if (dist[i] == INT_MAX)
				return (-1);
			if (dist[i] > max)
				max = dist[i];
		}
		return (max);
    }
};

// Dijkstra's algorithm - reusable template (C++17)
//
// Single-source shortest paths in a graph with NON-NEGATIVE edge weights.
// Time: O((V + E) log V).
//
// How to use:
//   1. Build the adjacency list. adj[u] holds {v, w} for each edge u -> v
//      of weight w.
//        - Directed graph:   push into adj[u] only.
//        - Undirected graph: also push the reverse {u, w} into adj[v].
//        - Nodes here are 0..n-1. For 1..n, size with n+1 and ignore index 0.
//   2. auto r = dijkstra(n, src, adj);
//        r.dist[i]   = shortest distance src -> i   (INF if unreachable)
//        r.parent[i] = previous node on that path   (-1 if none)
//   3. get_path(dst, r) returns the node sequence from src to dst
//      (empty if dst is unreachable).

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

struct DijkstraResult {
    vector<ll>  dist;    // dist[i]   = shortest distance from src to i
    vector<int> parent;  // parent[i] = predecessor of i on the shortest path
};

DijkstraResult dijkstra(int n, int src, const vector<vector<pair<int, ll>>>& adj) {
    vector<ll>  dist(n, INF);
    vector<int> parent(n, -1);

    // Min-heap of (distance, node). Distance is first so the smallest pops first.
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Skip stale entries: u was already settled with a shorter distance.
        // (This check replaces a separate visited[] array.)
        if (d > dist[u]) continue;

        // Relax every edge leaving u.
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});   // push only when the distance improves
            }
        }
    }
    return {dist, parent};
}

// Rebuild the shortest path src -> dst from the parent array.
// Returns an empty vector if dst is unreachable.
vector<int> get_path(int dst, const DijkstraResult& r) {
    if (r.dist[dst] == INF) return {};
    vector<int> path;
    for (int cur = dst; cur != -1; cur = r.parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());
    return path;
}

// ---- Example usage ----
int main() {
    int n = 5;                                  // nodes 0..4
    vector<vector<pair<int, ll>>> adj(n);

    auto add_edge = [&](int u, int v, ll w) {
        adj[u].push_back({v, w});
        // adj[v].push_back({u, w});            // uncomment for an undirected graph
    };

    add_edge(0, 1, 4);
    add_edge(0, 2, 1);
    add_edge(2, 1, 2);
    add_edge(1, 3, 1);
    add_edge(2, 3, 5);
    add_edge(3, 4, 3);

    int src = 0;
    DijkstraResult r = dijkstra(n, src, adj);

    for (int i = 0; i < n; ++i) {
        cout << "dist " << src << " -> " << i << " = ";
        if (r.dist[i] == INF) cout << "unreachable";
        else                  cout << r.dist[i];
        cout << "\n";
    }

    vector<int> path = get_path(4, r);
    cout << "path to 4:";
    for (int x : path) cout << ' ' << x;
    cout << "\n";

    return 0;
}