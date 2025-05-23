#include <bits/stdc++.h>
using namespace std;
 
static const int MOD = 1000000007;
 
void generateTransitions(int index, int mask1, int mask2, int n, 
                         vector<vector<int>>& transitions) {
    // If index exceeds n, stop (invalid path).
    if (index > n) return;
 
    // If we've exactly reached n, record the transition.
    if (index == n) {
        transitions[mask1].push_back(mask2);
        return;
    }
 
    // Case 1: current block is "1" in mask1
    generateTransitions(index + 1, mask1 | (1 << index), mask2, n, transitions);
 
    // Case 2a: current block is "0" in mask1, and "1" in mask2
    generateTransitions(index + 1, mask1, mask2 | (1 << index), n, transitions);
 
    // Case 2b: skip 2 blocks (like placing a horizontal domino)
    generateTransitions(index + 2, mask1, mask2, n, transitions);
}
 
int solveDP(int index, int mask, int n, int m, vector<vector<int>>& dp, const vector<vector<int>>& transitions) {
    if (index == m) {
        return (mask == 0 ? 1 : 0);
    }
 
    if (dp[index][mask] != -1) {
        return dp[index][mask];
    }
 
    long long answer = 0;
 
    for (auto newMask : transitions[mask]) {
        answer = (answer + solveDP(index + 1, newMask, n, m, dp, transitions)) % MOD;
    }
 
    return dp[index][mask] = answer;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, m;
    cin >> n >> m;
 
    int totalMasks = (1 << n);
    vector<vector<int>> transitions(totalMasks);
 
    generateTransitions(0, 0, 0, n, transitions);
 
    vector<vector<int>> dp(m + 1, vector<int>(totalMasks, -1));
 
    cout << solveDP(0, 0, n, m, dp, transitions) << "\n";
 
    return 0;
}
