/*This is a boiler plate template created by Hardik Aswal*/

/* Including all the libraries*/
#include<iostream>
#include<bits/stdc++.h>
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
#define vi vector<int>
#define mii map<int, int> 
#define mci map<char, int>
#define pii pair<int, int>
#define f(i,s,e)   for(int i=s;i<e;i++)

#define rf(i,s,e)     for(int i=s;i>=e;i--)
#define desc(vec) sort(vec.begin(), vec.end(), greater<int>());  
#define asc(vec)  sort(vec.begin(),vec.end());
#define maxo(x) *max_element((x).begin(), (x).end())
#define mino(x) *min_element((x).begin(), (x).end())
#define maxheap(type) priority_queue<type>
#define minheap(type) priority_queue<type, vector<type>, greater<type>>
#define sum(x) accumulate((x).begin(), (x).end(), 0LL)
#define sz(x) (int)(x.size())
#define all(x) x.begin(),x.end()
#define print(x) {for(auto v: x) {cout << v<< ' ';} cout << endl;}
#define printmap(x) {for(auto v: x) {cout << v.first << ':' << v.second << ' ';} cout << endl;}
#define printv(x) { for (auto v: x){ print(v) }}
#define print2d(vec,n,m) for(int i=0;i<=n;i++){for(int j=0;j<=m;j++)cout<<vec[i][j]<<" ";cout<<"\n";}
#define sp(x) fixed<<setprecision(x)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);









/*<---------------------------end of helper items-------------------------------------->*/
/*Defining Helper Functions*/

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}
int power(int a, int b) {
    int result = 1;
    while (b > 0) {
        
        if (b % 2 == 1) {
            result *= a;
        }
        a *= a;
        b /= 2;
    }
    return result;
}













/*<-----------------------------------end of helper functions-------------------------------->*/



double dp[301][301][301];
double fun(int& n, int x, int y, int z)
{
    //Base case
    if(x==0 && y==0 && z==0)
        return 0;
    if(x<0 || y<0 || z<0)
        return 0;
    if(dp[x][y][z] > -0.9)
        return dp[x][y][z];    
    double ans = n + (x*fun(n,x-1,y,z)) + (y*fun(n,x+1,y-1,z)) + (z*fun(n,x,y+1,z-1));
    return dp[x][y][z] = ans/(x+y+z);
}

int main()
{
    fast_io;
    
    memset(dp,-1,sizeof(dp));
    int n,j;
    cin>>n;

    int one=0,two=0,three=0;

    for(int i=0;i<n;i++)
    {
        cin>>j;
        if(j == 1)
        one++;
        else if(j == 2)
        two++;
        else
        three++;
    }
    cout<<sp(10)<<fun(n,one,two,three)<<endl;

    return 0;
}
