#include<bits/stdc++.h>
using namespace std;

const int N = 2e5+1, M =20;

vector<int>adj[N];
int dep[N], arr[N];
pair<int,int>Par[N][M];

void dfs(int cur, int par){
    for(int i=0;i<M;i++) Par[cur][i] ={0,INT_MAX};
    dep[cur] = dep[par] +1;
    Par[cur][0] = {par,min(arr[cur],arr[par])};
    for(int j=1;j<M;j++) Par[cur][j] = {Par[Par[cur][j-1].first][j-1].first ,
        min(Par[Par[cur][j-1].first][j-1].second,Par[cur][j-1].second) };
        for(auto x: adj[cur]) if( x!= par) dfs(x,cur);
}

int MinDistance(int u, int v){
    if(u ==v ) return u;
    if(dep[u]<dep[v]) swap(u,v);

    int diff = dep[u] - dep[v];
    int Mn = min(arr[u],arr[v]);
    for(int j = M-1;j>=0;j--){
        if((diff>>j) & 1) {
            u = Par[u][j].first;
            Mn = min(Mn,Par[u][j].second);

        }

    }
    
    for(int j = M-1;j>=0;j--){
        if(Par[u][j].first != Par[v][j].first){
            Mn = min(Par[u][j-1].second , min(Par[v][j-1].second,Mn));
            u = Par[u][j].first;
            v = Par[v][j].first;
        }

    }
    return (u!= v ? min(Mn,Par[u][0].second) : Mn);
}

int main(){
    int n,q; cin>>n>>q;
    for(int i=0; i<M;i++) Par[0][i] = {0,INT_MAX};
    for(int i=1;i<=n;i++) cin>>arr[i];
    

    for(int i=2;i<=n;i++){
        int x;
        cin>>x;
        adj[x].push_back(i);
    }

    dfs(1,1);

    for(int i=0;i<q;i++){
        int l,r; cin>>l>>r;
        cout<<MinDistance(l,r)<<endl;
    }
}