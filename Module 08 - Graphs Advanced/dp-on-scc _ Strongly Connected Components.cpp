#include <bits/stdc++.h>
using namespace std;

pair<vector<vector<int>>, vector<vector<int>>> kosaraju(
    vector<vector<int>> &adj) {
  constexpr int obi = 1;  // one based indexing
  int n = adj.size() - obi;

  // Getting the order of vertices in decreasing order of their finishing time.
  vector<int> vis(n + obi, 0), order;
  auto dfs = [&](auto &&dfs, int u) -> void {
    vis[u] = 1;
    for (int v : adj[u])
      if (!vis[v]) dfs(dfs, v);
    order.push_back(u);
  };
  for (int u = obi; u < n + obi; u++)
    if (!vis[u]) dfs(dfs, u);

  fill(vis.begin(), vis.end(), 0);
  reverse(order.begin(), order.end());

  // Getting the transpose of the graph.
  vector<vector<int>> adj_rev(n + obi);
  for (int u = obi; u < n + obi; u++)
    for (int v : adj[u]) adj_rev[v].push_back(u);

  vector<vector<int>> components;

  auto dfs_rev = [&](auto &&dfs_rev, int u) -> void {
    vis[u] = 1;
    components.back().push_back(u);
    for (int v : adj_rev[u])
      if (!vis[v]) dfs_rev(dfs_rev, v);
  };

  vector<int> roots(n + obi);

  // Getting the strongly connected components.
  for (int u : order) {
    if (vis[u]) continue;
    components.push_back({});
    dfs_rev(dfs_rev, u);
    vector<int> &component = components.back();
    int root = *min_element(component.begin(), component.end());
    for (int v : component) roots[v] = root;
  }

  // Getting the condensed graph.
  vector<vector<int>> adj_cond(n + obi);
  for (int u = obi; u < n + obi; u++)
    for (int v : adj[u])
      if (roots[u] != roots[v]) adj_cond[roots[u]].push_back(roots[v]);

  return {components, adj_cond};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }

  auto [components, adj_cond] = kosaraju(adj);
  vector<long long> vals(n + 1, 0);
  for (auto &component : components) {
    int root = *min_element(component.begin(), component.end());
    for (int u : component) vals[root] += a[u];
  }

  vector<long long> dp(n + 1, -1);

  auto dfs = [&](auto &&dfs, int u) -> void {
    if (dp[u] != -1) return;
    dp[u] = vals[u];
    for (int v : adj_cond[u]) {
      dfs(dfs, v);
      dp[u] = max(dp[u], vals[u] + dp[v]);
    }
  };
  for (int i = 1; i <= n; i++) dfs(dfs, i);

  cout << *max_element(dp.begin(), dp.end());

  return 0;
}