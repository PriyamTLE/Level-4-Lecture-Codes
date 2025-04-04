#include <bits/stdc++.h>
using namespace std;
 
struct Dsu {
  int n;
  vector<int> par, sz;
  Dsu(int n) : n(n) {
    par.resize(n + 1);
    sz.assign(n + 1, 1);
    for (int i = 0; i <= n; i++) par[i] = i;
  }
  int find(int u) { return par[u] = par[u] == u ? u : find(par[u]); }
  int size(int u) { return sz[find(u)]; }
  bool same(int u, int v) { return find(u) == find(v); }
  bool unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    par[v] = u, sz[u] += sz[v];
    return true;
  }
};
 
int main() {
  int n;
  cin >> n;
 
  vector<array<int, 2>> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i][0] >> a[i][1];
 
  vector<int> c(n + 1), k(n + 1);
  for (int i = 1; i <= n; i++) cin >> c[i];
  for (int i = 1; i <= n; i++) cin >> k[i];
 
  vector<pair<array<int, 2>, long long>> edges;
  for (int i = 1; i <= n; i++) edges.push_back({{0, i}, c[i]});
  for (int u = 1; u <= n; u++) {
    for (int v = 1; v <= n; v++) {
      if (u == v) continue;
      long long wt = 1LL * (k[u] + k[v]) *
                     (abs(a[u][0] - a[v][0]) + abs(a[u][1] - a[v][1]));
      edges.push_back({{u, v}, wt});
    }
  }
 
  sort(edges.begin(), edges.end(),
       [](auto l, auto r) { return l.second < r.second; });
 
  Dsu dsu(n + 1);
  long long cost = 0;
  vector<int> stations;
  vector<array<int, 2>> connections;
 
  for (auto [uv, wt] : edges) {
    auto [u, v] = uv;
    if (dsu.same(u, v)) continue;
    dsu.unite(u, v);
    cost += wt;
    if (u == 0)
      stations.push_back(v);
    else
      connections.push_back({u, v});
  }
 
  cout << cost << "\n" << stations.size() << "\n";
  for (int x : stations) cout << x << " ";
  cout << "\n" << connections.size() << "\n";
  for (auto [u, v] : connections) cout << u << " " << v << "\n";
 
  return 0;
}