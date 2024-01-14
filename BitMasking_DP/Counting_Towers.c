#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <string.h>

#define N (int)1e6+1
#define size 80
int dp[6];
int cache[N];
const int mod=(int)1e9+7;

enum States{
	UnderScore,Blank,Left_L,Right_L,t_shape,i_shape
};
// src     ->      destination
// states          transition 
// blank 		-> blank,underScore
// Left_L 		-> Left_L,Right_L,T,I
// Right_L 		-> Left_L,Right_L,T,I
// underScore 	-> blank,Right_L,Left_L,T,underScore,I,blank
// T    		-> blank,Right_L,Left_L,T,underScore,I,blank
// I    		-> T,Right_L,Left_L,I

// destionation <-  source
// state            state 
// underScore       blank,underScore,T
// blank            blank,underScore,T
// Left_L 		    Left_L,Right_L,T,I,underscore	
// Right_L 		    Left_L,Right_L,T,I,underscore	
// t_shape 		    underScore,Left_L,Right_L,T,I		
// i_shape 		    underScore,Left_L,Right_L,T,I			

void solve(){
	int n,i,answer=0;
	memset(dp,0,sizeof(dp)) ;
	assert(fscanf(stdin,"%d",&n)>0);
	if(cache[n]>0){
		printf("%d\n",cache[n]);
		return;
	}
	dp[UnderScore]=1;
	for(i=0;i<n;i++){
		if(i==(n-1)){
			int new_underScore = (dp[Blank]+dp[UnderScore])%mod;
			new_underScore = (new_underScore + dp[t_shape])%mod;
			int new_blank = new_underScore;
			
			int new_left_L = (dp[Left_L]+dp[Right_L])%mod;
			new_left_L = (new_left_L+dp[t_shape])%mod;
			new_left_L = (new_left_L+dp[i_shape])%mod;
			new_left_L = (new_left_L+dp[UnderScore])%mod;
			int new_right_L = new_left_L;
			int new_t_shape = new_right_L;

			dp[Blank] = 0; dp[UnderScore] = new_underScore;
			dp[Right_L] = 0; dp[Left_L] = 0;
			dp[t_shape] = new_t_shape; dp[i_shape] = 0;
		}
		else{
			// new state to temp_dp 
			int new_underScore = (dp[Blank]+dp[UnderScore])%mod;
			new_underScore = (new_underScore + dp[t_shape])%mod;
			int new_blank = new_underScore;
			
			int new_left_L = (dp[Left_L]+dp[Right_L])%mod;
			new_left_L = (new_left_L+dp[t_shape])%mod;
			new_left_L = (new_left_L+dp[i_shape])%mod;
			new_left_L = (new_left_L+dp[UnderScore])%mod;
			int new_right_L = new_left_L;
			
			int new_t_shape = new_right_L;
			int new_i_shape = new_right_L;

			dp[Blank] = new_blank; dp[UnderScore] = new_underScore;
			dp[Right_L] = new_right_L; dp[Left_L] = new_left_L;
			dp[t_shape] = new_t_shape; dp[i_shape] = new_i_shape;
		}
	}

	answer=(dp[UnderScore]+dp[t_shape])%mod;
	printf("%d\n",answer);
	cache[n]=answer;
	return;
}

int main(int argc,char const * argv[]){
	int tt;
	memset(cache,0,sizeof(cache));
	assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
	return 0;
}

// 2*1
//  __ __	
// |	  |
// (2*1) 1 way (no vertical bar)
//  __ __	
// |__|__|

// (2*1) 1 way (vertical bar)

// 2*2 (with vertical bar and without vertical bar)
//  __ __	   __ __     __ __     __ __
// |  |  | , |__|  | , |  |__| , |__|__|  

// dp[blank],dp[T],dp[Left_L],dp[Right_L],dp[I],dp[underscore]

// with vertical bar 4 choices (00,10,01,11)
//  __ __	   __ __ 
// |     |,  |__ __|,
// //  __ __     __ __ 
// // |__   | , |   __| , invalid moves 


// without vertical bar 4 choices (00,10,01,11)
//  __ __      __ __    __ __     __ __     __ __     
// |  |  | -> |  |  |  |  |  |   |  |  |   |  |  |   
// |     |    |  |  |, |__|  |,  |  |__|,  |__|__| , 
//  __ __      __ __    __ __     __ __     __ __     __ __    __ __
// |__|  | -> |__|  |  |__|  |   |__|  |   |__|  |   |__|  |  |__|  |
// |     |    |  |  |, |__|  |,  |  |__|,  |__|__| , |__ __| ,|     |

//  __ __      __ __    __ __     __ __     __ __     __ __    __ __
// |  |__| -> |  |__|  |  |__|   |  |__|   |  |__|   |  |__|  |  |__|
// |     |    |  |  |, |__|  |,  |  |__|,  |__|__| , |__ __| ,|     |

//  __ __      __ __    __ __     __ __     __ __     __ __    __ __
// |__|__| -> |__|__|  |__|__|   |__|__|   |__|__|   |__|__|  |__|__| 
// |     |    |  |  |, |__|  |,  |  |__|,  |__|__| , |__ __| ,|     |

//  __ __      __ __     __ __
// |     | -> |     |   |     | 
// |     |    |__ __|  ,|     |

// conversion from one form to another form 
// count of numbers ending with L(R),L(L),T , I and blank  for n-1 number 
// for nth item either we add T or __ 
