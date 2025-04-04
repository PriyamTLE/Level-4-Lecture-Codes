#include <bits/stdc++.h>
using namespace std;

vector<int> getTopoSort(vector<vector<int>> &adj) {
  constexpr int obi = 0;  // one based indexing
  int n = adj.size() - obi;
  vector<int> indegree(n + obi), topo;
  queue<int> q;
  for (int u = obi; u < n + obi; u++)
    for (int v : adj[u]) indegree[v]++;
  for (int u = obi; u < n + obi; u++)
    if (!indegree[u]) q.push(u);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topo.push_back(u);
    for (int v : adj[u])
      if (--indegree[v] == 0) q.push(v);
  }
  return topo.size() == n ? topo : vector<int>();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  vector<string> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  vector<vector<int>> adj(26);
  for (int i = 0; i < n - 1; i++) {
    bool diff = false;
    for (int j = 0; j < min(a[i].size(), a[i + 1].size()); j++) {
      if (a[i][j] != a[i + 1][j]) {
        adj[a[i][j] - 'a'].push_back(a[i + 1][j] - 'a');
        diff = true;
        break;
      }
    }
    if (!diff && a[i].size() > a[i + 1].size()) {
      cout << "Impossible";
      return 0;
    }
  }

  vector<int> topo = getTopoSort(adj);
  if (topo.empty())
    cout << "Impossible";
  else
    for (int i = 0; i < 26; i++) cout << char(topo[i] + 'a');

  return 0;
}