#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int,int>>> graph(n+1);
    vector<int> dist(n+1, INF);
    vector<bool> visited(n+1, false);
    
    // construct the graph
    for (auto edge : times) {
        int u = edge[0], v = edge[1], w = edge[2];
        graph[u].push_back({v, w});
    }
    
    // dijkstra's algorithm
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, k});
    dist[k] = 0;
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (auto neighbor : graph[u]) {
            int v = neighbor.first, w = neighbor.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    // check if all nodes are reachable and find the max distance
    int max_dist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) return -1;
        max_dist = max(max_dist, dist[i]);
    }
    
    return max_dist;
}

int main() {
    vector<vector<int>> times = {{2,1,1}, {2,3,1}, {3,4,1}};
    int n = 4, k = 2;
    int ans = networkDelayTime(times, n, k);
    cout << ans << endl; // output: 2
    return 0;
}
