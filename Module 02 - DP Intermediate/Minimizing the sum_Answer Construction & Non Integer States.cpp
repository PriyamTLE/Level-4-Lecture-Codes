#include<bits/stdc++.h>
using namespace std;
#define ll long long


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
