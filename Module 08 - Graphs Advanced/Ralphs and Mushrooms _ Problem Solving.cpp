#include <bits/stdc++.h>
using namespace std;

#define int long long

tuple<vector<vector<int>>, vector<vector<pair<int, int>>>, vector<int>>
kosaraju(vector<vector<pair<int, int>>> &adj) {
  constexpr int obi = 1;  // one based indexing
  int n = adj.size() - obi;

  // Getting the order of vertices in decreasing order of their finishing time.
  vector<int> vis(n + obi, 0), order;
  auto dfs = [&](auto &&dfs, int u) -> void {
    vis[u] = 1;
    for (auto [v, wt] : adj[u])
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
    for (auto [v, wt] : adj[u]) adj_rev[v].push_back(u);

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
    int root = component[0];
    for (int v : component) roots[v] = root;
  }

  // Getting the condensed graph.
  vector<vector<pair<int, int>>> adj_cond(n + obi);
  for (int u = obi; u < n + obi; u++)
    for (auto [v, wt] : adj[u])
      if (roots[u] != roots[v]) adj_cond[roots[u]].push_back({roots[v], wt});

  return {components, adj_cond, roots};
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, int>>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, wt;
    cin >> u >> v >> wt;
    adj[u].push_back({v, wt});
  }

  int src;
  cin >> src;

  auto [components, adj_cond, roots] = kosaraju(adj);
  vector<long long> val(n + 1, 0);

  set<pair<int, int>> natural_sum;
  for (int i = 0; i <= 1e5; i++) natural_sum.insert({i * (i + 1) / 2, i});

  for (auto &component : components) {
    int root = component[0];
    for (int u : component) {
      for (auto [v, wt] : adj[u]) {
        if (roots[v] != roots[u]) continue;
        int k = natural_sum.lower_bound({wt, 0})->second;
        long long curr = 1LL * k * wt - 1LL * (k - 1) * k * (k + 1) / 6;
        val[root] += curr;
      }
    }
  }

  vector<long long> dp(n + 1, -1);
  auto dfs = [&](auto &&dfs, int u) -> void {
    if (dp[u] != -1) return;
    dp[u] = val[u];
    for (auto [v, wt] : adj_cond[u]) {
      dfs(dfs, v);
      dp[u] = max(dp[u], val[u] + dp[v] + wt);
    }
  };
  src = roots[src];
  dfs(dfs, src);

  cout << dp[src] << "\n";

  return 0;
}