CSES
Dathi —  
Shared code
Link to this code: https://cses.fi/paste/ec0105dafa8bf6037d4db0/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
 
#define SZ 501
 
#define min(a,b) (a<=b)?(a):(b) 
#define max(a,b) (a>=b)?(a):(b) 
#define FOR(i,a,b) for(i=a;i<=b-1;i++)
#define ROF(i,a,b) for(i=b-1;i>=a;i--)
 
typedef void (*swap_func_t)(const void *,const void*,int,int);
typedef int (*comparator_t)(const void *,const void*,int,int);
 
const int mod =(int)1e9+7;
 int dp[SZ][SZ];
 
void solve(){
	int a,b,cnt=0,i,j,offset;
	assert(fscanf(stdin,"%d %d",&a,&b)>0);
	memset(dp,0,sizeof(dp));
	if(a>b){
		int t=a;a=b,b=t;
	}
	for(int width=1;width<=a;width++){	
		dp[width][width]=0;
		for(int height=width+1;height<=b;height++){
			if(width<4)	{
				dp[width][height] = 1+ dp[width][height-(height+1)/2] + dp[width][(height+1)/2];
				dp[height][width] = dp[width][height]; 
			}
			else{
				int maxi=(int)1e9+7;
				for(int offset=(height-1);offset>=1;offset--){
					int final = 1 + dp[width][height-offset] + dp[width][offset];
					if(maxi>final){
						maxi=final;
					}
				}
				for(int offset=width-1;offset>=1;offset--){
					int final = 1 + dp[width-offset][height] + dp[offset][height];
					if(maxi>final){
						maxi=final;
					}
				}
				dp[width][height] = maxi;
			    dp[height][width] = maxi;
			}
		}
	}
	printf("i am shit %d\n",dp[a][b]);
	//printf("%d %d %d\n",dp[a][b],dp[(a+1)/2][b],dp[a-((a+1)/2)][b]);
	return;
}
// minimum number of cuts to make rectangle a square 
 
int main(int argc,char const* argv[]){
	int tt;
	//assert(fscanf(stdin,"%d",&tt)>0);
	tt=1;
	while(tt--){
 
		solve();
	}
}
