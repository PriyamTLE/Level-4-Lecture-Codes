#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

int main() {
    int t, k;
    cin>>t>>k;

    vector<long long> dp(100005);
    dp[0] = 1;

    for(int i = 1; i < 100005; i++) {
        dp[i] += dp[i-1];

        if(i - k >= 0) { //! i = 3, when k = 4
            dp[i] += dp[i-k];
        }

        dp[i] %= MOD;
    }

    vector<long long> presum = dp;

    for(int i = 1; i < dp.size(); i++) {
        presum[i] += presum[i-1];

        presum[i] %= MOD;
    }

    while(t--) {
        int a, b;
        cin>>a>>b;

        long long ans = (presum[b] - presum[a-1]) % MOD;

        if(ans < 0) ans += MOD;

        cout<<ans<<"\n";
    }

    return 0;
}