#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const long long INF = 1e14;

vector<long long> dijkstra(vector<vector<pair<int, int>>> &graph, int source, int n) {
    vector<long long> distance(2 * n + 5, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        pair<long long, int> current = pq.top();
        pq.pop();
        long long dist_u = current.first;
        int u = current.second;

        if (dist_u > distance[u]) continue;

        for (pair<int, int> &edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
            }
        }
    }

    return distance;
}

int main() {
    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        int n, m, h;
        cin >> n >> m >> h;

        vector<vector<pair<int, int>>> graph(2 * n + 5);
        vector<int> horses(h);
        for (int i = 0; i < h; i++) {
            cin >> horses[i];
        }

        for (int i = 0; i < m; i++) {
            int a, b, w;
            cin >> a >> b >> w;
            graph[2 * a].push_back({2 * b, w});
            graph[2 * b].push_back({2 * a, w});
            graph[2 * a + 1].push_back({2 * b + 1, w / 2});
            graph[2 * b + 1].push_back({2 * a + 1, w / 2});
        }

        for (int i = 1; i <= n; i++) {
            graph[2 * i + 1].push_back({2 * i, 0});
        }

        for (int i = 0; i < h; i++) {
            int x = horses[i];
            graph[2 * x].push_back({2 * x + 1, 0});
        }

        vector<long long> dist_from_2 = dijkstra(graph, 2, n);
        vector<long long> dist_from_2n = dijkstra(graph, 2 * n, n);

        long long answer = INF;
        for (int i = 2; i <= 2 * n + 1; i++) {
            answer = min(answer, max(dist_from_2[i], dist_from_2n[i]));
        }

        if (answer == INF) {
            answer = -1;
        }

        cout << answer << '\n';
    }

    return 0;
}
