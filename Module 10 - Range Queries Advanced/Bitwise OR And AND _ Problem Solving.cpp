const int BITS = 32;
vector<SegTree> seg(BITS);  // One segment tree per bit position (32-bit integers)
vector<vector<int>> bitArr(BITS, vector<int>(n, 0));  // Stores bit-wise representation

for (int b = 0; b < BITS; b++) {
    for (int i = 0; i < n; i++) {
        bitArr[b][i] = (arr[i] >> b) & 1;  // Extract b-th bit of arr[i]
    }
    seg[b].init(n);  // Initialize segment tree
    seg[b].build(bitArr[b], 0, 0, n - 1);  // Build with bit values
}






// Answering the Queries
while (m--) {
    int type; cin >> type;
    
    if (type == 1) {
        int L, R, X;
        cin >> L >> R >> X;

        for (int b = 0; b < BITS; b++) {
            if ((X >> b) & 1) {
                seg[b].update(0, 0, n - 1, L - 1, R - 1);
            }
        }

    } else if (type == 2) {
        int L, R;
        cin >> L >> R;
        int ans = 0;
        int len = R - L + 1;

        for (int b = 0; b < BITS; b++) {
            int cnt = seg[b].query(0, 0, n - 1, L - 1, R - 1);  // number of set bits at b-th position
            ans += (1 << b) * cnt;  // contribute to sum
        }

        cout << ans << "\n";
    }
}
