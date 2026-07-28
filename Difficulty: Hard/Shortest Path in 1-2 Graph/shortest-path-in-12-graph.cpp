#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Solution {
public:
    // Updated parameter order to match the GfG driver code
    int shortestPath(int V, int src, int dest, vector<vector<int>>& edges) {
        
        // Step 1: Build the adjacency list
        // adj[u] will store pairs of {neighbor_vertex, edge_weight}
        vector<vector<pair<int, int>>> adj(V);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w}); // Graph is undirected
        }

        // Step 2: Initialize distance array with infinity
        vector<int> dist(V, numeric_limits<int>::max());
        dist[src] = 0;

        // Step 3: Min-heap priority queue to store {current_distance, vertex}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        // Step 4: Process the graph
        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Optimization: If we've reached the destination, we can stop early
            if (node == dest) return currentDist;

            // If we have already found a shorter path to this node, skip it
            if (currentDist > dist[node]) continue;

            // Traverse all adjacent nodes
            for (const auto& neighbor : adj[node]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;

                // Relaxation step
                if (dist[node] + weight < dist[nextNode]) {
                    dist[nextNode] = dist[node] + weight;
                    pq.push({dist[nextNode], nextNode});
                }
            }
        }

        // Step 5: If destination is unreachable, return -1
        if (dist[dest] == numeric_limits<int>::max()) {
            return -1;
        }
        
        return dist[dest];
    }
};