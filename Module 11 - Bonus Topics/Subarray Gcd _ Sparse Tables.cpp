#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
const int LOG = 20;

int st[MAXN][LOG];
int logTable[MAXN];

void buildLog(int n) {
    logTable[1] = 0;
    for (int i = 2; i <= n; i++) {
        logTable[i] = logTable[i / 2] + 1;
    }
}

void buildSparseTable(const vector<int>& a, int n) {
    for (int i = 0; i < n; i++) {
        st[i][0] = a[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            st[i][j] = __gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int gcdQuery(int l, int r) {
    int j = logTable[r - l + 1];
    return __gcd(st[l][j], st[r - (1 << j) + 1][j]);
}
int countSubarraysWithGCDAtLeastX(const vector<int>& a, int x) {
    int n = a.size();
    buildLog(n);
    buildSparseTable(a, n);

    int count = 0;
    for (int i = 0; i < n; i++) {
        int lo = i, hi = n - 1, pos = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (gcdQuery(i, mid) >= x) {
                pos = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (pos != -1) {
            count += (pos - i + 1);
        }
    }
    return count;
}
int main() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int& val : a) cin >> val;

    int result = countSubarraysWithGCDAtLeastX(a, x);
    cout << result << '\n';
    return 0;
}
