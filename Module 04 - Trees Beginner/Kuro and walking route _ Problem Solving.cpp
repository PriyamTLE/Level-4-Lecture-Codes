#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

vector<int> g[N];
vector<int> sub_size(N);
vector<int> intime(N), outtime(N);

int cur_time = 0;

void dfs(int node, int par)
{
    sub_size[node] = 1; //! helps in leaf nodes
    intime[node] = cur_time++; //! intime of node

    for (auto child : g[node])
    {
        if (child == par)
            continue;
        dfs(child, node);
        sub_size[node] += sub_size[child];
    }

    outtime[node] = cur_time++; //! outtime
}

bool is_ancestor(int node_a, int node_b) //! checks if node_a is ancestor of node_b
{
    if ((intime[node_a] <= intime[node_b]) and (outtime[node_a] >= outtime[node_b]))
        return true;
    return false;
}

int main()
{
    int n, x, y;
    cin >> n >> x >> y;

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(y, 0);

    long long ans = (long long)(n) * (n - 1);

    long long val = n;

    for (auto child : g[y])
    {
        if (is_ancestor(child, x))
        {
            val -= sub_size[child];
            break;
        }
    }

    ans -= (long long)(sub_size[x]) * val;

    cout << ans << "\n";

    return 0;
}