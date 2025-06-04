#include <bits/stdc++.h>

using namespace std;

long long dp[105][100005];

int main()
{
    int n, w;
    cin >> n >> w;

    vector<long long> weight(n), value(n);

    for (int i = 0; i < n; i++)
    {
        cin >> weight[i] >> value[i];
    }

    int sum = accumulate(value.begin(), value.end(), 0);

    //! in old dp, n * capacity
    //! in new dp, n * sum of values of the array

    for (int val = 1; val <= sum; val++)
        dp[0][val] = INT_MAX;

    for (int i = 1; i <= n; i++)
    {
        for (int val = 0; val <= sum; val++)
        {
            if (val >= value[i - 1])
            {
                dp[i][val] = min(weight[i - 1] + dp[i - 1][val - value[i - 1]], dp[i - 1][val]);
            }
            else
            {
                dp[i][val] = dp[i - 1][val];
            }
        }
    }

    int ans = 0;
    for (int val = 0; val <= sum; val++)
    {
        if (dp[n][val] <= w)
            ans = max(ans, val);
    }

    cout << ans << "\n";

    return 0;
}