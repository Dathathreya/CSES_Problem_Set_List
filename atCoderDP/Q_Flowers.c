#include <stdio.h>
#include <string.h>
#include <assert.h>

#define N ((int)2e5+1)
typedef long long unsigned  llu;
int h[N],a[N],sz=0;
llu sgtree[(1<<20)];

llu max(llu a,llu b){
	return (a>=b)?(a):(b);
}

void update(int pos,llu value){
	pos += sz;	
	sgtree[pos] = value;
	pos >>= 1;
	for(;pos>0;){
		sgtree[pos] = max(sgtree[2*pos],sgtree[2*pos+1]);
		pos >>= 1;
	}
	return;
}

llu query(int start,int end){
	llu answer=0;
	start += sz;
	end  += sz;
	while(start<=end){
		if((start%2)==1){ 
			// need to move our start forward bc if we skip this start will be updated to smth
			// where least reachable start from this node is lesser than our intended start
			answer=max(sgtree[start++],answer);
		}
		if((end%2)==0){
			// need to move our end backward bc if we skip this end will be updated to smth
			// where greatest reachable end from this node is greater than our intended end
			answer=max(sgtree[end--],answer);
		}
		start >>= 1;
		end  >>= 1;
	}
	return answer;
}

void solve(){
	int n,i;
	assert(fscanf(stdin,"%d",&n)>0);
	while((1<<sz)<=n){
		sz++;
	}
	sz = 1<<sz;
	// 8 , 16(n=10 can be fitted into 16)
	for(i=0;i<n;i++){
		assert(fscanf(stdin,"%d",&h[i])>0);
	}
	for(i=0;i<n;i++){
		assert(fscanf(stdin,"%d",&a[i])>0);
	}
	memset(sgtree,0,sizeof(sgtree));
	// o(n^2) -> o(nlogn)
	for(i=0;i<n;i++){
		// what is the ending height having maximum score with its ending height lesser than current height
		/*
		o(n*n)
		for(int ending=0;ending<currheight;ending++){
			if((dp[currheight])<(dp[ending]+a[i])){
				dp[currheight] = dp[ending]+a[i];
				maxi = (maxi<dp[currheight])?(dp[currheight]):(maxi);
			}
		}
		*/ 
		// o(nlogn)
		int currheight = h[i];
		llu prevMaxBeauty = query(0,currheight-1); 
		update(currheight-1,prevMaxBeauty+a[i]); 
	}
	printf("\n%llu\n",sgtree[1]);	
	return;
}

int main(){
	int tt=1;
	// assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
