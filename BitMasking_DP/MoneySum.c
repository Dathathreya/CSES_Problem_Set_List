CSES
Dathi —  
Shared code
Link to this code: https://cses.fi/paste/ddcf173c3a5be8357d5095/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
 
#define N 501
 
#define min(a,b) (a<=b)?(a):(b) 
#define max(a,b) (a>=b)?(a):(b) 
#define FOR(i,a,b) for(i=a;i<=b-1;i++)
#define ROF(i,a,b) for(i=b-1;i>=a;i--)
#define Empty 0
 
const int mod =(int)1e9+7;
int dp[100006],a[N];
 
int compare(const void* a,const void* b){
	return (*(int*)a) - (*(int*)b);
} 
 
void solve(){
	int n,i,num,x,cnt=0;
	assert(fscanf(stdin,"%d",&n)>0);
	memset(dp,0,sizeof(dp));
	dp[Empty]=1;
	FOR(i,0,n){
		assert(fscanf(stdin,"%d",&a[i])>0);
	}
	//100*1000+1
	qsort(a,n,sizeof(int),compare);
	FOR(i,0,n){
		ROF(num,1,100006){
			if((num>=a[i])&&(dp[num-a[i]])){
				dp[num]=1;
			}
		}
	}
 
	FOR(i,1,100006){
		if(dp[i]){
			cnt+=1;
		}
	}
	printf("%d\n",cnt);
	FOR(i,1,100006){
		if(dp[i]){
			printf("%d ",i);
		}
	}
	return;
}
 
int main(int argc,char const* argv[]){
	int tt;
	//assert(fscanf(stdin,"%d",&tt)>0);
	tt=1;
	while(tt--){
 
		solve();
	}
}
https://cses.fi/paste/ddcf173c3a5be8357d5095/
