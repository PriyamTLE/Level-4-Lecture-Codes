#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        vector<int> weights(n + 1), degree(n + 1);

        for (int i = 1; i <= n; i++)
            cin >> weights[i];

        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            degree[a]++;
            degree[b]++;
        }

        priority_queue<int> pq;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j < degree[i] - 1; j++)
                pq.push(weights[i]);
        }

        long long sum = accumulate(weights.begin(), weights.end(), 0LL);

        cout << sum << " ";

        for (int i = 2; i < n; i++)
        {
            sum += pq.top();
            pq.pop();

            cout << sum << " ";
        }

        cout << "\n";
    }
}