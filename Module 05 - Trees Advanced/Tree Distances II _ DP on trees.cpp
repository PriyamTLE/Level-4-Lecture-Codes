#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    vector<int> subtree(n + 1, 1), answer(n + 1);

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    function<int(int, int, int)> dfs = [&](int node, int parent, int depth) {
        int answer = depth;
        for (auto &i : adj[node]) {
            if (i != parent) {
                answer += dfs(i, node, depth + 1);
                subtree[node] += subtree[i];
            }
        }
        return answer;
    };

    function<void(int, int, int)> reroot = [&](int node, int parent, int ans) {
        answer[node] = ans;
        for (auto &i : adj[node]) {
            if (i != parent) {
                reroot(i, node, ans + n - 2 * subtree[i]);
            }
        }
    };

    reroot(1, 1, dfs(1, 1, 0));

    for (int i = 1; i <= n; i++) {
        cout << answer[i] << " ";
    }
    cout << endl;

    return 0;
}
