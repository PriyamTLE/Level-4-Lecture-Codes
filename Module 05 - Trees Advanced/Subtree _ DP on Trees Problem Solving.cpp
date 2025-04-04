#include <bits/stdc++.h>
using namespace std;

int power(int a, int b, int m) {
  int res = 1;
  while (b) {
    if (b & 1) res = 1LL * res * a % m;
    a = 1LL * a * a % m;
    b >>= 1;
  }
  return res;
}

int inv(int a, int m) { return power(a, m - 2, m); }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  m = 1e9 + 7;  // since the class is for the learning purpose, we are using the
                // modulo 1e9 + 7. In the original problem, m can be anything in
                // the range 2 to 1e9.

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // dp[u] -> number of ways for subtree of u when u is black colored.
  vector<int> dp(n + 1), ans(n + 1);

  function<void(int, int)> dfs = [&](int u, int p) {
    dp[u] = 1;
    for (int v : adj[u]) {
      if (v == p) continue;
      dfs(v, u);
      dp[u] = 1LL * dp[u] * (dp[v] + 1) % m;
    }
  };
  dfs(1, 0);

  auto changeRoot = [&](int u, int v) {
    dp[u] = 1LL * dp[u] * inv(dp[v] + 1, m) % m;
    dp[v] = 1LL * dp[v] * (dp[u] + 1) % m;
  };

  function<void(int, int)> reroot = [&](int u, int p) {
    ans[u] = dp[u];
    for (int v : adj[u]) {
      if (v == p) continue;
      changeRoot(u, v);
      reroot(v, u);
      changeRoot(v, u);
    }
  };
  reroot(1, 0);

  for (int i = 1; i <= n; i++) cout << ans[i] << " ";

  return 0;
}