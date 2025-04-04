#include <bits/stdc++.h> 
 
using namespace std;
 
typedef long long ll;
typedef pair<ll,ll> p64;
typedef vector<ll> v64;
ll MOD = 998244353;
double eps = 1e-12;
#define forn(i,e) for(ll i = 0; i < e; i++)
#define forsn(i,s,e) for(ll i = s; i < e; i++)
#define ln "\n"
#define pb push_back
#define fi first
#define se second
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())

class SegmentTree {
  ll n;
  v64 arr;
  v64 seg;

public :
  SegmentTree(v64 arr) {
    this->n = sz(arr);
    this->arr = arr;

    seg.resize(4*n + 1);
    build(0, 0, n-1);
  }

  void build(ll ind, ll low, ll high) {
    if(low == high) {
      seg[ind] = arr[low];
      return;
    }

    ll mid = (low + high) / 2;

    build(2*ind+1, low, mid);
    build(2*ind+2, mid+1, high);

    seg[ind] = (seg[2*ind+1] + seg[2*ind+2]);
  }

  ll query(ll ind, ll low, ll high, ll start, ll end) {
    //! no overlap
    if((end < low) or (start > high)) {
      return 0;
    }

    //! complete overlap
    if((low >= start) and (high <= end)) {
      return seg[ind];
    }

    //! partial overlap
    ll mid = (low + high) / 2;
    
    ll left = query(2*ind+1, low, mid, start, end);
    ll right = query(2*ind+2, mid+1, high, start, end);

    return (left + right);
  }

  void point_update(ll ind, ll low, ll high, ll node, ll val) {
    if(low == high) {
      seg[ind] = val;
      return;
    }

    ll mid = (low + high) / 2;

    if(node <= mid) {
      point_update(2*ind+1, low, mid, node, val);
    }
    else {
      point_update(2*ind+2, mid+1, high, node, val);
    }

    seg[ind] = (seg[2*ind+1] + seg[2*ind+2]);
  }
};


 
void solve(){
  ll n;
  cin>>n;

  v64 v(n);
  forn(i, n) {
    cin>>v[i];
    if(i % 2 == 1) v[i] *= -1;
  }

  SegmentTree seg(v);

  ll q;
  cin>>q;

  forn(_, q) {
    ll x, a, b;
    cin>>x>>a>>b;

    if(x == 0) {
      a--;

      if(a % 2 == 0) {
        seg.point_update(0, 0, n-1, a, b);
      }
      else {
        seg.point_update(0, 0, n-1, a, -b);
      }
    }
    else {
      a--;
      b--;

      ll val = seg.query(0, 0, n-1, a, b);

      if(a % 2 == 1) val *= -1;

      cout<<val<<ln;
    }
  }
}
int main()
{
//freopen("input.txt", "r", stdin);
//freopen("output.txt", "w", stdout);

 fast_cin();
 ll t = 1;
//  cin >> t;
 for(int it=1;it<=t;it++) {
  //cout << "Case #" << it+1 << ": ";
  solve();
 }
 return 0;
}