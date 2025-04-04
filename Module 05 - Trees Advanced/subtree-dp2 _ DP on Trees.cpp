#include <bits/stdc++.h>
using namespace std;

void dfs(int node, int parent, vector<int> &val, vector<vector<int>> &adj,
         vector<vector<int>> &dp) {
  dp[node][0] = 0;
  dp[node][1] = val[node];
  for (int neighbor : adj[node]) {
    if (neighbor == parent) continue;
    dfs(neighbor, node, val, adj, dp);
    dp[node][0] += max(dp[neighbor][0], dp[neighbor][1]);
    dp[node][1] += dp[neighbor][0];
  }
}

int main() {
  int n;
  cin >> n;

  vector<int> val(n + 1);
  for (int i = 1; i <= n; i++) cin >> val[i];

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // dp[i][0] = maximum value of the subtree rooted at i if we don't take node i
  // dp[i][1] = maximum value of the subtree rooted at i if we take node i
  vector<vector<int>> dp(n + 1, vector<int>(2));

  dfs(1, 0, val, adj, dp);

  cout << max(dp[1][0], dp[1][1]);

  return 0;
}