#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int n;
  cin >> n;
 
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];
 
  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
 
  const int LOG = 20;  // make sure 2 ^ LOG >= n
  vector<int> lvl(n + 1);
  vector<vector<int>> par(n + 1, vector<int>(LOG));
  vector<vector<int>> mx(n + 1, vector<int>(LOG));
 
  auto dfs = [&](auto &&dfs, int u, int p) -> void {
    lvl[u] = lvl[p] + 1;
    par[u][0] = p;
    mx[u][0] = a[u];
    for (int v : adj[u]) {
      if (v == p) continue;
      dfs(dfs, v, u);
    }
  };
 
  for (int j = 1; j < LOG; j++) {
    for (int i = 1; i <= n; i++) {
      int mid = par[i][j - 1];
      par[i][j] = par[mid][j - 1];
      mx[i][j] = max(mx[i][j - 1], mx[mid][j - 1]);
    }
  }
 
  auto lift = [&](int u, int k) {
    for (int j = 0; j < LOG; j++) {
      if (k >> j & 1) {
        u = par[u][j];
      }
    }
    return u;
  };
 
  auto get_max = [&](int u, int k) {
    int res = 0;
    for (int j = 0; j < LOG; j++) {
      if (k >> j & 1) {
        res = max(res, mx[u][j]);
        u = par[u][j];
      }
    }
    return res;
  };
 
  auto lca = [&](int u, int v) {
    if (lvl[u] < lvl[v]) swap(u, v);
    u = lift(u, lvl[u] - lvl[v]);
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; j--) {
      if (par[u][j] != par[v][j]) {
        u = par[u][j];
        v = par[v][j];
      }
    }
    return par[u][0];
  };
 
  auto dist = [&](int u, int v) {
    int l = lca(u, v);
    return lvl[u] + lvl[v] - 2 * lvl[l];
  };
 
  auto get_max_on_path = [&](int u, int v) {
    int l = lca(u, v);
    return max(
        {get_max(u, lvl[u] - lvl[l]), get_max(v, lvl[v] - lvl[l]), a[l]});
  };
 
  int q;
  cin >> q;
 
  while (q--) {
    int u, v;
    cin >> u >> v;
 
    // Answer the queries depending on the problem.
  }
 
  return 0;
}