#include <bits/stdc++.h>
using namespace std;

vector<int> getTopoSort(vector<vector<pair<int, int>>> &adj) {
  constexpr int obi = 0;  // one based indexing
  int n = adj.size() - obi;
  vector<int> vis(n + obi, 0), topo;
  auto dfs = [&](auto &&dfs, int u) -> void {
    vis[u] = 1;
    for (auto [v, wt] : adj[u])
      if (!vis[v]) dfs(dfs, v);
    topo.push_back(u);
  };
  for (int u = obi; u < n + obi; u++)
    if (!vis[u]) dfs(dfs, u);
  reverse(topo.begin(), topo.end());
  return topo;
}

int heaviest_path(vector<vector<pair<int, int>>> &adj) {
  int n = adj.size();
  vector<int> topo = getTopoSort(adj);
  vector<int> dp(n, 0);
  for (int i = n - 1; i >= 0; i--) {
    int u = topo[i];
    for (auto [v, wt] : adj[u])
      dp[u] = max(dp[u], dp[v] + wt);
  }
  return *max_element(dp.begin(), dp.end());
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, int>>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v, wt;
    cin >> u >> v >> wt;
    u--, v--;
    adj[u].push_back({v, wt});
  }

  cout << heaviest_path(adj);

  return 0;
}