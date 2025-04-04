class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        const int INF = 1e8;
        vector<int> dist(n, INF);
        dist[src] = 0;
        for (int i = 0; i < k + 1; i++) {
            vector<int> ndist = dist;
            for (auto &flight : flights) {
                int u = flight[0], v = flight[1], wt = flight[2];
                if (dist[u] != INF) ndist[v] = min(ndist[v], dist[u] + wt);
            }
            dist = ndist;
        }
        return dist[dst] == INF ? -1 : dist[dst];
    }
};