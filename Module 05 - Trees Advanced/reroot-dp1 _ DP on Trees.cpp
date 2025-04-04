#include <bits/stdc++.h>
using namespace std;

void dfs(int node, int parent, vector<int> &val, vector<int> &subtree_size,
         vector<vector<int>> &adj, vector<long long> &dp) {
  subtree_size[node] = 1;
  dp[node] = 0;
  for (int neighbor : adj[node]) {
    if (neighbor == parent) continue;
    dfs(neighbor, node, val, subtree_size, adj, dp);
    subtree_size[node] += subtree_size[neighbor];
    dp[node] += dp[neighbor] +
                1LL * subtree_size[neighbor] * (val[node] ^ val[neighbor]);
  }
}

void changeRoot(int oldRoot, int newRoot, vector<int> &val,
                vector<int> &subtree_size, vector<long long> &dp) {
  subtree_size[oldRoot] -= subtree_size[newRoot];
  dp[oldRoot] -=
      dp[newRoot] + 1LL * subtree_size[newRoot] * (val[oldRoot] ^ val[newRoot]);

  subtree_size[newRoot] += subtree_size[oldRoot];
  dp[newRoot] +=
      dp[oldRoot] + 1LL * subtree_size[oldRoot] * (val[oldRoot] ^ val[newRoot]);
}

void reroot(int node, int parent, vector<int> &val, vector<int> &subtree_size,
            vector<vector<int>> &adj, vector<long long> &dp,
            vector<long long> &ans) {
  ans[node] = dp[node];
  for (int neighbor : adj[node]) {
    if (neighbor == parent) continue;
    changeRoot(node, neighbor, val, subtree_size, dp);
    reroot(neighbor, node, val, subtree_size, adj, dp, ans);
    changeRoot(neighbor, node, val, subtree_size, dp);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) {
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

    vector<int> subtree_size(n + 1);
    vector<long long> dp(n + 1), ans(n + 1);

    dfs(1, 0, val, subtree_size, adj, dp);
    reroot(1, 0, val, subtree_size, adj, dp, ans);

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
  }

  return 0;
}