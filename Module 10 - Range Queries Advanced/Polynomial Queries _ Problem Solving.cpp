void push(int start, int ending, int node) {
    if (lazy[node].second) { // If there's a pending update
        int len = ending - start + 1;

        // Update the current node with the sum of AP
        st[node] += len * (lazy[node].first - lazy[node].second) + lazy[node].second * len * (len + 1) / 2;

        if (start != ending) {
            int diff = ((start + ending) / 2 + 1) - start;

            // Propagate to the left child
            lazy[2 * node + 1].first += lazy[node].first;
            lazy[2 * node + 1].second += lazy[node].second;

            // Propagate to the right child
            lazy[2 * node + 2].first += lazy[node].first + diff * lazy[node].second;
            lazy[2 * node + 2].second += lazy[node].second;
        }

        // Clear the lazy value at current node
        lazy[node] = {0, 0};
    }
}






void update(int start, int ending, int node, int l, int r) {
    push(start, ending, node);

    if (start > r || ending < l) return;

    if (start >= l && ending <= r) {
        lazy[node] = {(start - l + 1), 1};  // Initial term = (start - l + 1), common difference = 1
        push(start, ending, node);
        return;
    }

    int mid = (start + ending) / 2;
    update(start, mid, 2 * node + 1, l, r);
    update(mid + 1, ending, 2 * node + 2, l, r);

    // Merge results
    st[node] = st[2 * node + 1] + st[2 * node + 2];
}
