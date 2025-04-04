#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<array<int, 2>> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1];

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    using ll = long long;
    vector<vector<ll>> dp(n + 1, vector<ll>(2));

    function<void(int, int)> dfs = [&](int u, int p) {
      dp[u][0] = dp[u][1] = 0;
      for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        for (int i = 0; i <= 1; i++) {
          dp[u][i] += max(dp[v][0] + abs(a[u][i] - a[v][0]),
                          dp[v][1] + abs(a[u][i] - a[v][1]));
        }
      }
    };
    dfs(1, 0);

    cout << max(dp[1][0], dp[1][1]) << "\n";
  }

  return 0;
}