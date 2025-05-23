#include<bits/stdc++.h>

using namespace std;
#define pb push_back
#define ll long long




ll main(){
  

    ll n;
    cin>>n;
    vector<pair<ll,ll>>vp(n);
    for(ll i=0;i<n;i++){
        cin>>vp[i].first>>vp[i].second;
    }

    vector<vector<ll>>dp(n,vector<ll>(1<<n,-1));
    auto cost = [&](ll i,ll j) -> ll {
        return abs(vp[i].first - vp[j].first) + abs(vp[i].second - vp[j].second);
    };

    auto f = [&](ll prev, ll mask, auto &&F) -> ll {

        ll index = __builtin_popcount(mask);
        if(index == n) return 0;

        if(dp[prev][mask] != -1) return dp[prev][mask];

        ll ans = 1e8;

        for(ll i=0;i<n;i++){
            if((mask & (1<<i)) == 0){
                answer = min(answer, (index != 0  ? cost(i,prev) : 0) + F(i,mask|(1<<i)) );

            }
        }
        return dp[prev][mask] = answer;
    }; 
    f(0,0,f);






}
