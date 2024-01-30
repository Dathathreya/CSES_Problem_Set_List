#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#define N (int)910010

#define FOR(i,a,b) for(i=a;i<=b-1;i++)
#define ROF(i,a,b) for(i=b-1;i>=a;i--)
#define max(a,b) (a>=b)?(a):(b)
#define min(a,b) (a<=b)?(a):(b)


typedef long long unsigned lli;
const int mod = (int)1e9+7;

const lli INF = ULLONG_MAX;
lli maxi=(long long)1e18;
lli dp[401][401],prefix[401],a[401];

void solve(){
    int n,i;
    assert(fscanf(stdin,"%d",&n));
    
    memset(prefix,0,sizeof(prefix));

    FOR(i,0,n){
        assert(fscanf(stdin,"%llu",&a[i]));
        if(i==0){
            prefix[i]=a[i];
        }
        else{
            prefix[i] = (prefix[i-1]+a[i]);
        }
    }
    memset(dp,0,sizeof(dp));
    for(int gap=1;gap<=n-1;gap++){
        for(int start=0;gap+start<n;start++){
            if(gap==1){
                dp[start][start+gap]= (a[start]+a[start+gap]);
            }
            else{
                maxi=INF;
                int end = start+gap;
                for(int k=start;k<=end-1;k++){

                maxi = min(maxi,(dp[start][k]+dp[k+1][end]+prefix[end]-((start<=0)?(0):(prefix[start-1])) ));
                }
                dp[start][end]=maxi;
            }
        }
    }
    printf("%llu\n",dp[0][n-1]);
}

int main(){
    int tt=1;
    
    while((tt--)){
        solve();
    }
}
