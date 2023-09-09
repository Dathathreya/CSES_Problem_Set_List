#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mxN = 2e5+5;
int dp[mxN];
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int n,i; cin>>n;
    pair<int,int> a[n+1];
    a[0]={-1,-1};
    for ( i = 1; i <= n; i++) 
       { cin>>a[i].first;
            a[i].second=(i);
       }
    sort(a, a+n+1);
    int cnt=0;
    for(i=1;i<=n;i++)
    {
        if(a[i].second>a[i-1].second){

        }
        else{
            cnt+=1;
        }
    }
    printf("%lld\n",cnt+1);
}
