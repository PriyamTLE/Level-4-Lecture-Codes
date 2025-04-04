#include <bits/stdc++.h>
using namespace std;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
 
  int n;
  cin >> n;
 
  vector dist(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) cin >> dist[i][j];
 
  vector<int> order(n);
  for (int i = n - 1; i >= 0; i--) cin >> order[i], order[i]--;
 
  vector<long long> ans(n);
 
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int u = order[i], v = order[j], m = order[k];
        dist[u][v] = min(dist[u][v], dist[u][m] + dist[m][v]);
        if (i <= k && j <= k) ans[k] += dist[u][v];
      }
    }
  }
 
  for (int i = n - 1; i >= 0; i--) cout << ans[i] << " ";
 
  return 0;
}