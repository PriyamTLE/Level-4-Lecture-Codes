#include<bits/stdc++.h>

using namespace std;
#define ll long long

const ll Ksize = 10001;
const ll D =101;
const ll MOD = 1e9+7;


string s;
ll d;
ll dp[Ksize][2][D];

ll f(ll index ,ll tight ,ll sum){
    if(index == s.length()){
       if(sum==0) return 1;
       return 0;
    }
    if(dp[index][tight][sum] != -1) return dp[index][tight][sum];
    ll ans =0;

    ll bound = (tight ? s[index]-'0' : 9);
    ll answer =0;
    for(ll i=0;i<=bound;i++){
        answer = (answer + f(index + 1, (tight & s[index]-'0' == i), (sum + i)%d)) % MOD;

    }
    return dp[index][tight][sum] = answer;
}



int main(){
    cin>>s>>d;
    memset(dp,-1,sizeof(dp));
    cout<<f(0,1,0) -1 <<endl;

}
