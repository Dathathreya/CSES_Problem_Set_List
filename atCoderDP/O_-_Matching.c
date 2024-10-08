// https://atcoder.jp/contests/dp/tasks/dp_o
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define O 21 
typedef long long int lli;
typedef long long unsigned llu;
#define mod ((int)1e9+7)
int dp[1<<O]; // (2)^n
bool mism[21][21];

int bpcnt(int num){
	int cnt = 0;
	while(num>0){
		cnt++;
		num = num&(num-1);
	}
	return cnt;
}

int modadd(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

void solve(){
	int n,women,bit,ans=0,men=0;
	short temp;
	assert(fscanf(stdin,"%d",&n)>0);
	memset(dp,0,sizeof(dp));
	for(men=0;men<n;men++){
		for(women=0;women<n;women++){
			assert(fscanf(stdin,"%hd",&temp)>0);
			mism[men][women]= temp?true:false;
		}
	}
/*	
	approach:
	we maintain count of pairs of men and women matched up in prev iterations	
	in bitmask.
	each time we consider a new men-women pair to be added we take and fill
	vacant bits not taken if men-women pair is allowed.
	we take bitset_count for mask to know how many of them are free for current allowed
	men-women pair to be filled in there.
	but there are no restriction on choice of wi we take to pair it with current men_j as long 
	as bit wi is free .
	example :
women_indexing:12345678 : j 
     men_mask: 01001010 - mask representing men_i paired up with  women_j
	
		builtin_popcount - 3
		so we pair 4th men can be paired up with 1st,3rd,4th,6th and 8th women in current iteration
		for current mask which has its respective count.
	we iterate through each non-set bit and pair up current men_i with women_j
	which results in a new mask as current mask contributes to that new_mask		
	similarly we have someother mask contributing to same new_mask 

	for example: we pair up 4th men with 1st women resulting mask will be 11001010.
		women_indexing:12345678 : j 
		     we need to iterate through all these open vacant positions bit by bit for each mask
     		 men_mask: 01001010 -
     		 			M1 M2 M3
     		 	010001100
     		 	123456789
     		 	0_M1_000_M2__M3_00 		


    but we could also havesomething like below,pairing up 4th men with 2nd women 
    resulting mask will be 11001010. 		 
    women_indexing:12345678 : j 
         men_mask: 10001010 - 		two different masks contributing to same mask.

	dp[0] = 1; // base condition otherwise other transitions wont work.
	for example pairing 1st men with 1st women 
	before:
		women_indexing:12345678 : j   12345678 
     		 men_mask: 00000000 -> 	  10000000 this pair wont be considered as 1 if dp[0] is not 1.
*/
	dp[0] = 1;
	for(int mask=0;mask<((1<<n)-1);mask++){ // bitmask representing previous matched pairs
			int filled=bpcnt(mask);
			for(int women=0;women<n;women++){ // 2^n thats not set in bitmask as mentioned in above approach.
				if((((1<<women)&mask)==0)&&(mism[filled][women])){
					dp[mask^(1<<women)] = modadd(dp[mask^(1<<women)],dp[mask]);
				}
		}
	}
	printf("%d\n",dp[(1<<n)-1]);
	return;
}

int main(){
	int tt=1;
	// assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
