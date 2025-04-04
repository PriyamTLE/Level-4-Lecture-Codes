#include <bits/stdc++.h>

using namespace std;

long long dp[5005][5005];

long long fun(int i, int j, vector<long long> &v) {
    if(i > j) return 0;

    if(dp[i][j] != -1) return dp[i][j];

    long long x = v[i] + min(fun(i+2, j, v), fun(i+1, j-1, v));
    long long y = v[j] + min(fun(i+1, j-1, v), fun(i, j-2, v));

    return dp[i][j] = max(x, y);
}

int main() {
    int n;
    cin>>n;

    vector<long long> v(n);

    for(int i = 0; i < n; i++) cin>>v[i];

    memset(dp, -1, sizeof(dp));

    cout<<fun(0, n-1, v);
    
    return 0;
}