#include <bits/stdc++.h>
using namespace std;

void dfs(int node, int parent, vector<vector<int>> &adj,
         vector<int> &subtree_size, vector<long long> &dp) {
  subtree_size[node] = 1;
  dp[node] = 0;
  for (int neighbor : adj[node]) {
    if (neighbor == parent) continue;
    dfs(neighbor, node, adj, subtree_size, dp);
    subtree_size[node] += subtree_size[neighbor];
    dp[node] += dp[neighbor] + subtree_size[neighbor];
  }
}

int main() {
  int n;
  cin >> n;

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> subtree_size(n + 1, 0);
  vector<long long> dp(n + 1, 0);

  dfs(1, 0, adj, subtree_size, dp);

  for (int i = 1; i <= n; i++) cout << dp[i] << " ";

  return 0;
}