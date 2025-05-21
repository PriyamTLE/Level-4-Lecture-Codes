/*This is a boiler plate template created by Hardik Aswal*/

/* Including all the libraries*/
#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<unordered_map>
#include<set>
#include<cmath>
#include<algorithm>
#include<climits>
#include<deque>
#include<unordered_set>
#include<map>


/*<----------------------------------end of libraries-------------------------------------->*/

using namespace std;
/*Defining helper items*/

#define pb push_back
#define ll long long
#define mod 1000000007
//#define mod2 998244353
#define vi vector<ll>
#define mii map<ll, ll> 
#define mci map<char, ll>
#define pii pair<ll, ll>
#define f(i,s,e)   for(ll i=s;i<e;i++)

#define rf(i,s,e)     for(ll i=s;i>=e;i--)
#define desc(vec) sort(vec.begin(), vec.end(), greater<ll>());  
#define asc(vec)  sort(vec.begin(),vec.end());
#define maxo(x) *max_element((x).begin(), (x).end())
#define mino(x) *min_element((x).begin(), (x).end())
#define maxheap(type) priority_queue<type>
#define minheap(type) priority_queue<type, vector<type>, greater<type>>
#define sum(x) accumulate((x).begin(), (x).end(), 0LL)
#define sz(x) (ll)(x.size())
#define all(x) x.begin(),x.end()
#define print(x) {for(auto v: x) {cout << v<< ' ';} cout << endl;}
#define printmap(x) {for(auto v: x) {cout << v.first << ':' << v.second << ' ';} cout << endl;}
#define printv(x) { for (auto v: x){ print(v) }}
#define print2d(vec,n,m) for(ll i=0;i<=n;i++){for(ll j=0;j<=m;j++)cout<<vec[i][j]<<" ";cout<<"\n";}









/*<---------------------------end of helper items-------------------------------------->*/
/*Defining Helper Functions*/

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
ll lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}
ll power(ll a, ll b) {
    ll result = 1;
    while (b > 0) {
        
        if (b % 2 == 1) {
            result *= a;
        }
        a *= a;
        b /= 2;
    }
    return result;
}


ll solve(ll ind ,ll k,vector<ll>&a,vector<vector<ll>>&dp){
    ll n = a.size();
    if(ind >= n) return 0;
    if(dp[ind][k]!=-1) return dp[ind][k];

    ll ans = LLONG_MAX;

    // case 1 not take the element at index ind

    ll nt = a[ind] + solve(ind+1,k,a,dp);

    // Case 2 take the element and make subarray of size 2 - k + 1;

    ll t = LLONG_MAX;
    ll har = a[ind];
    for(ll j = ind+1; j <= ind+k && j < n; j++){

        har = min(har,a[j]);
        t = min(t, har*(j-ind+1) + solve(j+1,k-j+ind,a,dp));

    }
    ans = min(ans,min(t,nt));
    return dp[ind][k] = ans;

}











/*<-----------------------------------end of helper functions-------------------------------->*/





int main(){
  ll t;
  cin >> t;
  while(t--){   
    ll n,k;
    cin>>n>>k;
    vector<ll>a(n);

    for(ll i=0;i<n;i++){
        cin>>a[i];
    }
    vector<vector<ll>>dp(n+2,vector<ll>(k+2,-1));
    cout<<solve(0,k,a,dp)<<endl;
    

  }


}
