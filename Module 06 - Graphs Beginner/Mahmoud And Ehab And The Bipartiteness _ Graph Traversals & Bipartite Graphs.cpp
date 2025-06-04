#include <bits/stdc++.h>
using namespace std;

int col[2] = {0, 0};

void dfs(int node, int parent, int color, vector<vector<int>> &adj) {
    col[color]++;
    for (auto &i : adj[node]) {
        if (i != parent) {
            dfs(i, node, color ^ 1, adj);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0, 0, adj);

    cout << 1LL * col[0] * col[1] - (n - 1) << "\n";

    return 0;
}
