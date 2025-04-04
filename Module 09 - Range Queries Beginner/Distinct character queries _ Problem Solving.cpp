#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> p32;
typedef pair<ll, ll> p64;
typedef pair<double, double> pdd;
typedef vector<ll> v64;
typedef vector<int> v32;
typedef vector<vector<int>> vv32;
typedef vector<vector<ll>> vv64;
typedef vector<vector<p64>> vvp64;
typedef vector<p64> vp64;
typedef vector<p32> vp32;
ll MOD = 998244353;
double eps = 1e-12;
#define forn(i, e) for (ll i = 0; i < e; i++)
#define forsn(i, s, e) for (ll i = s; i < e; i++)
#define rforn(i, s) for (ll i = s; i >= 0; i--)
#define rforsn(i, s, e) for (ll i = s; i >= e; i--)
#define ln "\n"
#define dbg(x) cout << #x << " = " << x << ln
#define pb push_back
#define fi first
#define se second
#define INF 2e18
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())

class SegmentTree {
    ll n;
    v64 arr;
    vector<array<ll, 26>> seg;

public : 
    SegmentTree(v64 arr) {
        n = sz(arr);
        this->arr = arr;

        seg.resize(4*n + 1);
        build(0, 0, n-1);
    }

    void merge(array<ll, 26> &left, array<ll, 26> &right, array<ll, 26> &node) {
        forn(i, 26) node[i] = left[i] + right[i];
    }

    void build(ll ind, ll low, ll high) {
        if(low == high) {
            seg[ind][arr[low]] = 1;
            return;
        }

        ll mid = (low + high) / 2;
        build(2*ind + 1, low, mid);
        build(2*ind + 2, mid+1, high);

        merge(seg[2*ind + 1], seg[2*ind + 2], seg[ind]);
    }

    array<ll, 26> query(ll ind, ll low, ll high, ll start, ll end) {
        if((start > high) or (end < low)) {
            return array<ll, 26>{};
        }

        if((low >= start) and (high <= end)) {
            return seg[ind];
        }

        ll mid = (low + high) / 2;

        array<ll, 26> left = query(2*ind + 1, low, mid, start, end);
        array<ll, 26> right = query(2*ind + 2, mid+1, high, start, end);

        array<ll, 26> ans;
        merge(left, right, ans);

        return ans;
    }

    void update(ll ind, ll low, ll high, ll node, ll val) {
        if(low == high) {
            seg[ind][arr[low]] = 0;
            arr[low] = val;
            seg[ind][arr[low]] = 1;
            return;
        }

        ll mid = (low + high) / 2;

        if(node <= mid) {
            update(2*ind + 1, low, mid, node, val);
        }
        else {
            update(2*ind + 2, mid+1, high, node, val);
        }

        merge(seg[2*ind + 1], seg[2*ind + 2], seg[ind]);
    }
};

void solve()
{
    string s;
    cin>>s;

    ll n = sz(s);

    v64 arr(n);
    forn(i, n) arr[i] = s[i] - 'a';

    SegmentTree seg(arr);

    ll q;
    cin>>q;

    forn(_, q) {
        ll a;
        cin>>a;

        if(a == 1) {
            ll b; char c;
            cin>>b>>c;
            seg.update(0, 0, n-1, b-1, (c-'a'));
        }
        else {
            ll b, c;
            cin>>b>>c;

            array<ll, 26> tmp = seg.query(0, 0, n-1, b-1, c-1);
            ll ans = 0;
            forn(i, 26) ans += (tmp[i] != 0);

            cout<<ans<<ln;
        }
    }
}
int main()
{
    fast_cin();
    ll t = 1;
    // cin >> t;
    for (int it = 1; it <= t; it++)
    {
        // cout << "Case #" << it+1 << ": ";
        solve();
    }
    return 0;
}