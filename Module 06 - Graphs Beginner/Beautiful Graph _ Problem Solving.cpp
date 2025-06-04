#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 999;
const int MOD = 998244353;

int n, m;
vector<int> graph[MAXN];
int powerOfTwo[MAXN];
int color[MAXN];
int countColor[2];
bool isNotBipartite;

void dfs(int node, int currentColor) {
    color[node] = currentColor;
    ++countColor[currentColor];

    for (int neighbor : graph[node]) {
        if (color[neighbor] == -1) {
            dfs(neighbor, 1 - currentColor);
        } else if (color[neighbor] == currentColor) {
            isNotBipartite = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute powers of 2 modulo MOD
    powerOfTwo[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        powerOfTwo[i] = (2 * powerOfTwo[i - 1]) % MOD;
    }

    int testCases;
    cin >> testCases;

    while (testCases--) {
        cin >> n >> m;

        // Clear graph and reset color
        for (int i = 0; i < n; ++i) {
            graph[i].clear();
            color[i] = -1;
        }

        // Read edges
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u, --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int result = 1;
        bool failed = false;

        for (int i = 0; i < n; ++i) {
            if (color[i] != -1) continue;

            isNotBipartite = false;
            countColor[0] = countColor[1] = 0;

            dfs(i, 0);

            if (isNotBipartite) {
                cout << 0 << "\n";
                failed = true;
                break;
            }

            int ways = (powerOfTwo[countColor[0]] + powerOfTwo[countColor[1]]) % MOD;
            result = (1LL * result * ways) % MOD;
        }

        if (!failed) {
            cout << result << "\n";
        }
    }

    return 0;
}
