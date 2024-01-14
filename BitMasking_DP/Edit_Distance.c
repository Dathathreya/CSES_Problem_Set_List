#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define M 5001
#define min(a,b) (a<=b)?(a):(b) 

char ch1[M],ch2[M];
int dp[M+1][M+1];

void solve(){
	int src,des,n,m;
	memset(dp,0,sizeof(dp));
	assert(fscanf(stdin,"%s %s",&ch1,&ch2)>0);
	//fprintf(stderr,"%s %s\n",ch1,ch2);
	n=strlen(ch1),m=strlen(ch2);
	/*how many characters need to delete from src to match des("") empty string*/
	for(src=0;src<=n;src++){
		dp[src][0]=src;
	}
	/*how many characters need to be inserted to empty src("") to match des */
	for(des=0;des<=m;des++){
		dp[0][des]=des;
	}

	for(src=1;src<=n;src++){
		for(des=1;des<=m;des++){
			if(ch1[src-1]==ch2[des-1]){
				dp[src][des] = dp[src-1][des-1];
			}
			else{
				int insertion = dp[src][des-1]+1; // insert des'th character and move des'th back because des'th already matches
				int deletion  = dp[src-1][des]+1; //delete src'th character and move src'th back
												  // because src'th character not included in comparison	
				int replacement = dp[src-1][des-1]+1; // replace src'th character with des'th character
													  // move src and des back as both matches	
				int curr  = min(insertion,deletion);
				curr = min(curr,replacement);
				dp[src][des] = curr;
			}
		}
	}
	printf("%d\n",dp[n][m]);
}

// https://codeforces.com/problemset/problem/626/F
// https://codeforces.com/contest/1920

int main(int argc,char const* argv[]){
	int tt;
	//assert(fscanf(stdin,"%d",&tt)>0);
	tt=1;
	while(tt--){
		solve();
	}
}


// 		des -
// 		 0  1 2 3 4 5
// 	src  "" M O V I E 	
// 	|    
// 0   ""   0  1 2 3 4 5  -> insertion of char to src to match des 
// 1   L    1  1 
// 2   O    2
// 3   V    3
// 4   E    4

// (dp[src-1][des-1]+1)replacement 
// (dp[src-1][des]+1,des[src][des-1]+1)

// 		 -> deletion of char from src to match des 
