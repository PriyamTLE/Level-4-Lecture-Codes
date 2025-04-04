#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;
ll MOD = 998244353;
double eps = 1e-12;
#define forn(i, e) for (ll i = 0; i < e; i++)
#define forsn(i, s, e) for (ll i = s; i < e; i++)
#define ln "\n"
#define pb push_back
#define fi first
#define se second
#define fast_cin()                  \
  ios_base::sync_with_stdio(false); \
  cin.tie(NULL);                    \
  cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())

struct s
{
  ll val = 0;
  v64 fre;
};

class SegmentTree
{
public:
  ll n;
  v64 arr;
  vector<s> seg;

  SegmentTree(v64 arr)
  {
    n = sz(arr);
    this->arr = arr;

    seg.resize(4 * n + 1);
    build(0, 0, n - 1);
  }

  void merge(s &node, s &left, s &right)
  {
    node.val = left.val + right.val;
    node.fre.resize(41, 0);

    v64 pre = right.fre;
    forsn(i, 1, 41) pre[i] += pre[i - 1];

    forsn(i, 1, 41)
    {
      node.val += left.fre[i] * pre[i - 1];
    }

    forn(i, 41)
    {
      node.fre[i] = left.fre[i] + right.fre[i];
    }
  }

  void build(ll ind, ll low, ll high)
  {
    if (low == high)
    {
      seg[ind].fre.resize(41, 0);
      seg[ind].fre[arr[low]] = 1;
      return;
    }

    ll mid = (low + high) / 2;

    build(2 * ind + 1, low, mid);
    build(2 * ind + 2, mid + 1, high);

    merge(seg[ind], seg[2 * ind + 1], seg[2 * ind + 2]);
  }

  s query(ll ind, ll low, ll high, ll start, ll end)
  {
    //! no overlap
    if ((end < low) or (start > high))
    {
      s tmp;
      tmp.fre.resize(41, 0);

      return tmp;
    }

    //! complete overlap
    if ((start <= low) and (end >= high))
    {
      return seg[ind];
    }

    ll mid = (low + high) / 2;

    s left = query(2 * ind + 1, low, mid, start, end);
    s right = query(2 * ind + 2, mid + 1, high, start, end);

    s ans;
    merge(ans, left, right);

    return ans;
  }

  void point_update(ll ind, ll low, ll high, ll node, ll val)
  {
    if (low == high)
    {
      seg[ind].fre[arr[low]] = 0;
      arr[low] = val;
      seg[ind].fre[arr[low]] = 1;
      return;
    }

    ll mid = (low + high) / 2;

    if (node <= mid)
    {
      point_update(2*ind + 1, low, mid, node, val);
    }
    else
    {
      point_update(2*ind + 2, mid+1, high, node, val);
    }

    merge(seg[ind], seg[2 * ind + 1], seg[2 * ind + 2]);
  }
};

void solve()
{
  ll n, q;
  cin >> n >> q;

  v64 v(n);
  forn(i, n) cin >> v[i];

  SegmentTree seg(v);

  forn(_, q)
  {
    ll x, a, b;
    cin >> x >> a >> b;

    if (x == 1)
    {
      a--;
      b--;

      cout << seg.query(0, 0, n - 1, a, b).val << ln;
    }
    else
    {
      a--;

      seg.point_update(0, 0, n - 1, a, b);
    }
  }
}
int main()
{
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);

  fast_cin();
  ll t = 1;
  //  cin >> t;
  for (int it = 1; it <= t; it++)
  {
    // cout << "Case #" << it+1 << ": ";
    solve();
  }
  return 0;
}