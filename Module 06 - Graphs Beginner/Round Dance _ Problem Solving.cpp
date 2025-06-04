#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define ll long long

void dfs(int i, vector<int>& a, vector<int>& vis, int c, map<int, vector<int>>& adj) {
    vis[i] = c;

    for (auto it : adj[i]) {
        if (vis[it] == 0) {
            dfs(it, a, vis, c, adj);
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        map<int, vector<int>> adj;
        for (int i = 1; i <= n; i++) {
            adj[i].pb(a[i]);
            adj[a[i]].pb(i);
        }

        vector<int> vis(n + 1, 0);
        int c = 1;
        for (int i = 1; i <= n; i++) {
            if (vis[i] == 0) {
                dfs(i, a, vis, c, adj);
                c++;
            }
        }

        int maxo = c - 1;
        map<int, int> nodes;
        for (int i = 1; i <= n; i++) nodes[vis[i]]++;

        set<pair<int, int>> st;
        map<int, int> cnt;
        for (int i = 1; i <= n; i++) {
            int c1 = min(i, a[i]);
            int c2 = max(i, a[i]);
            st.insert({c1, c2});
        }

        for (auto i : st) {
            cnt[vis[i.first]]++;
        }

        int comp = 0;
        for (int i = 1; i <= c; i++) {
            if (cnt[i] != nodes[i]) {
                comp++;
            }
        }

        int mino = maxo;
        if (comp > 0) mino -= (comp - 1);
        cout << mino << " " << maxo << endl;
    }
}
