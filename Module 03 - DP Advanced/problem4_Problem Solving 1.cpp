#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX;

struct Friend {
    long long x, k;
    int p;
    Friend(long long x, long long k, int p) : x(x), k(k), p(p) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long b;
    cin >> n >> m >> b;

    vector<Friend> friends;
    for (int i = 0; i < n; ++i) {
        long long x, k;
        int mm, p = 0;
        cin >> x >> k >> mm;
        for (int j = 0; j < mm; ++j) {
            int skill;
            cin >> skill;
            p |= 1 << (skill - 1);
        }
        friends.emplace_back(x, k, p);
    }

    sort(friends.begin(), friends.end(), [](const Friend &a, const Friend &b) {
        return a.k < b.k;
    });

    vector<long long> dp(1 << m, INF);
    dp[0] = 0;
    long long res = INF;

    for (const auto& f : friends) {
        vector<long long> new_dp = dp;
        for (int mask = 0; mask < (1 << m); ++mask) {
            if (dp[mask] < INF) {
                int new_mask = mask | f.p;
                new_dp[new_mask] = min(new_dp[new_mask], dp[mask] + f.x);
            }
        }
        dp = new_dp;
        if (dp[(1 << m) - 1] < INF) {
            res = min(res, dp[(1 << m) - 1] + b * f.k);
        }
    }

    if (res == INF) {
        cout << -1 << '\n';
    } else {
        cout << res << '\n';
    }

    return 0;
}
