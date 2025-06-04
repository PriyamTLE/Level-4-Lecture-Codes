// Push Function

void push(int start, int ending, int node) {
    if (lazy[node]) {
        st[node] = (ending - start + 1) - st[node];  // Flip the number of set bits

        if (start != ending) {
            lazy[2 * node + 1] ^= lazy[node];  // Propagate the flip to left child
            lazy[2 * node + 2] ^= lazy[node];  // Propagate the flip to right child
        }

        lazy[node] = 0;  // Clear the current node's lazy value
    }
}


// Walk Function

int walk(int start, int ending, int k, int node) {
    push(start, ending, node);

    if (start == ending) return start;

    int mid = (start + ending) / 2;

    push(start, mid, 2 * node + 1);  // Ensure left child is updated

    if (st[2 * node + 1] >= k) {
        return walk(start, mid, k, 2 * node + 1);  // Go left
    }

    return walk(mid + 1, ending, k - st[2 * node + 1], 2 * node + 2);  // Go right, subtracting left size
}
