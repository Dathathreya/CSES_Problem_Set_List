#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define N (int)2e5+4
#define min(a,b) (a<=b)?(a):(b)
int dp[N],a[N];
//#define abs(A) (A>0)?(A):(-A)

void solve(){
    int n,i,j;
    assert(fscanf(stdin,"%d",&n)>0);
    memset(dp,0x7f,sizeof(dp));
    dp[0]=0; /* as i stay here no cost */
    for(i=0;i<n;i++){
        assert(fscanf(stdin,"%d",&a[i])>0);
    }
    for(i=1;i<n;i++){
        for(j=1;(j<=2)&&((j+i-1)<n);j++){
            dp[(i-1)+j] = min((dp[(i-1)+j]),(dp[i-1]+abs((a[i-1]-a[j+(i-1)]))));
        }
    }
    printf("%d\n",dp[n-1]);
}

int main(){
    int tt=1;
    // assert(fscanf(stdin,"%d",&tt)>0);
    while(tt--)
        solve();
}
