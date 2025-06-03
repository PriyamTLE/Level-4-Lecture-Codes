#include <bits/stdc++.h>
using namespace std;



const int MOD = 1000000007;
const int MAXN = 200007;

vector<int> ans, adj[MAXN];
bool visited[MAXN];
int inputOrder[MAXN], relativeOrder[MAXN];

bool compareByInputOrder(int a, int b) {
    return relativeOrder[a] < relativeOrder[b];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        cin >> inputOrder[i];
        relativeOrder[inputOrder[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end(), compareByInputOrder);
    }

    queue<int> q;
    q.push(1);
    fill(visited, visited + n + 1, false);

    while (!q.empty()) {
        queue<int> tempQueue;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            ans.push_back(node);
            visited[node] = true;
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    tempQueue.push(neighbor);
                }
            }
        }
        q = tempQueue;
    }

    for (int i = 0; i < n; i++) {
        if (inputOrder[i] != ans[i]) {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes\n";
    return 0;
}
