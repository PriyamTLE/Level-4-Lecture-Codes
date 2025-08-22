#include <bits/stdc++.h>
using namespace std;

vector<int> root;
vector<int> sz;
set<int> conCom;

int par(int x) {
    if (x == root[x])
        return x;
    else
        return root[x] = par(root[x]);
}

bool join(int a, int b) {
    a = par(a);
    b = par(b);

    if (a == b)
        return false;

    if (sz[a] > sz[b]) swap(a, b);

    sz[b] += sz[a];

    conCom.erase(root[a]);
    root[a] = b;

    return true;
}

int main() {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    vector<int> g[n+1];
    root.resize(n+1, 0);
    sz.resize(n+1, 0);

    for(int i = 1; i <= n; i++) {
        root[i] = i;
        sz[i] = 1;
    }

    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> isOpen(n+1, 0);

    vector<int> queries(n);

    for(int i = 0; i < n; i++) cin >> queries[i];

    vector<int> ans;

    for(int i = n-1; i >= 0; i--) {
        int node = queries[i];
        conCom.insert(root[node]);
        isOpen[node] = 1;

        for(auto child : g[node]) {
            if(isOpen[child]) {
                join(node, child);
            }
        }

        if(conCom.size() == 1) ans.push_back(1);
        else ans.push_back(0);
    }

    reverse(ans.begin(), ans.end());

    for(int i = 0; i < n; i++) {
        cout << (ans[i] == 1 ? "YES" : "NO") << "\n";
    }

    return 0;
}
