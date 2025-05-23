#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 1;

int f(int index, int leftToSkip, vector<int>&pos, vector<int>&speed, vector<vector<int>>&dp) {
    if(index == speed.size() - 1) return 0;
    if(dp[index][leftToSkip] != -1) return dp[index][leftToSkip];

    int answer = INT_MAX;

    for(int i = index + 1; i < speed.size() && (i - (index + 1)) <= leftToSkip; i++) {
        answer = min(answer, f(i, leftToSkip - (i - (index + 1)), pos, speed, dp) + (pos[i] - pos[index]) * speed[index]);
    } 

    return dp[index][leftToSkip] = answer;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n, l, k; cin >> n >> l >> k;

    vector<int>pos(n + 1), speed(n + 1); pos[n] = l;

    for(int i = 0; i < n; i++) cin >> pos[i];
    for(int i = 0; i < n; i++) cin >> speed[i];

    vector<vector<int>>dp(n, vector<int>(k + 1, -1));
    cout << f(0, k, pos, speed, dp) << "\n";    
}