#include <bits/stdc++.h>

using namespace std;

void dfs(int node, int par, vector<int> g[], vector<int> &sub_size, int &num_edges_removed, int x)
{
    sub_size[node] = 1;

    for (auto child : g[node])
    {
        if (child == par)
            continue;
        dfs(child, node, g, sub_size, num_edges_removed, x);
        sub_size[node] += sub_size[child];
    }

    if (node == 1)
    {
        if (sub_size[node] < x)
            num_edges_removed--;
    }
    else
    {
        if (sub_size[node] >= x)
        {
            num_edges_removed++;
            sub_size[node] = 0;
        }
    }
}

int bs(int n, int k, vector<int> g[], vector<int> &sub_size)
{
    int low = 1, high = n;

    int ans = 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        int num_edges_removed = 0;

        dfs(1, 0, g, sub_size, num_edges_removed, mid);

        if (num_edges_removed >= k)
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return ans;
}
int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, k;
        cin >> n >> k;

        vector<int> g[n + 5], sub_size(n + 5);

        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            g[a].push_back(b);
            g[b].push_back(a);
        }

        cout << bs(n, k, g, sub_size) << "\n";
    }

    return 0;
}