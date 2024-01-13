#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const int mod=1e9+7;
#define N (int)1e6+1
#define M 101
#define max(a,b) (a>=b)?(a):(b)
#define min(a,b) (a<=b)?(a):(b)
#define FOR(i,a,b) for(i=a;i<b;i++)
#define ROF(i,a,b) for(i=b-1;i>=a;i--)
int dp[M],dp_temp[M];

// https://cses.fi/problemset/result/8177610/

void solve(){
	int n,m,i,x,StartsWithZero=0,curr;
	assert(fscanf(stdin,"%d %d",&n,&m)>0);
	assert(fscanf(stdin,"%d",&x)>0);
	StartsWithZero = (x==0);
	int answer = 0;
	memset(dp,0,sizeof(dp));memset(dp_temp,0,sizeof(dp_temp));
	if(StartsWithZero){
		// set count # of all numbers to 1
		for(curr=1;curr<=m;curr++)
		{	dp[curr]=1;    }
	}
	else{
		// set count # of x to 1
		dp[x]=1;
	}
	FOR(i,1,n){
		assert(fscanf(stdin,"%d",&x)>0);
		if(x==0){
			memset(dp_temp,0,sizeof(dp_temp));
			for(curr=1;curr<=m;curr++){
				// find count # of numbers ending with curr 
				// curr->curr,curr+1->curr,curr-1->curr (3 transitions) 
				// so count has 3 states  example as last
				int oneLess = (curr==1)?(0):(dp[curr-1]%mod);
				int same    =  dp[curr]%mod;
				int oneMore = (curr==m)?(0):(dp[curr+1]%mod);
				oneLess = (oneLess+same)%mod;
				oneLess = (oneLess+oneMore)%mod;
				dp_temp[curr] = oneLess;
			}
			memcpy(dp,dp_temp,sizeof(dp_temp));
		}
		else{
			int oneLess = (x==1)?(0):(dp[x-1]%mod);
			int same    = dp[x]%mod;
			int oneMore = (x==m)?(0):(dp[x+1]%mod);
			memset(dp,0,sizeof(dp));
			oneLess = (oneLess+same)%mod;
			oneLess = (oneLess+oneMore)%mod;
			dp[x]   = oneLess ;
		}
	}
	FOR(i,1,(m+1)){
		answer = (answer + dp[i])%mod;
	}
	printf("%d\n",answer);
}

int main(){
	int tt=1;
	//assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}

//  example 
// 	   3 0 0 3 0 0  0 0  2    0
// 1   0 0 1 0 0 4 12 32 0    116 same-1 
// 2   0 1 2 0 4 8 20 48 116  116 same
// 3   1 1 2 4 4 8 16 36 0    116 same+1

// 0116
// 0116
// 232
// 116
// 348 --> final count

// https://atcoder.jp/contests/dp/tasks
//https://cses.fi/problemset/task/2183

// https://usaco.guide/problems/cses-1746-array-description/solution
