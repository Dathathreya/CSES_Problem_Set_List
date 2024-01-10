#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const int mod=1e9+7;
#define N (int)1e6+1
#define max(a,b) (a>=b)?(a):(b)
#define min(a,b) (a<=b)?(a):(b)
#define FOR(i,a,b) for(i=a;i<b;i++)
#define ROF(i,a,b) for(i=b-1;i>=a;i--)

#define swap(type ,a,b) \
	type c = a;\
	a=b,b=c;

#define pair_struct(type1,type2)\
typedef struct pair_##type1##_##type2{\
	type1 first;type2 second;\
}pair_##type1##_##type2;


typedef int (*comparator_t)(const void* a,int,int); 
typedef void (*swap_func_t)(const void* b,int,int); 
typedef long long  ll;typedef long long int lli; typedef long long unsigned llu;

pair_struct(int,int);
pair_int_int pairs[N];
int dp[N];

int comparePII(const void* a,int first,int second){
	pair_int_int* temp = (pair_int_int*)a;
	double f1=(temp[first].second)/(1.0*temp[first].first);
	double f2=(temp[second].second)/(1.0*temp[second].first);
	return f1<=f2;
}

void swapPII(const void* a,int first,int second){
	pair_int_int* temp = (pair_int_int*)a;
	swap(pair_int_int,(temp[first]),(temp[second]));
	return;
}


void merger(const void* a,int start,int mid,int end,comparator_t comp_func,swap_func_t swap_func){
	int start2=mid+1;
	if(comp_func(a,mid,start2)){
		return;
	}
	while(((start2<=end)&&(start<=mid))){
		if(comp_func(a,start,start2)){
			start++;
		}
		else{
			int index = start2;
			//2 3 4 5 6 7 8 9 1 
			while(index!=start){
				  if(comp_func(a,index,index-1))	 /*swap only when prev < curr */
					swap_func(a,index,index-1);
				index-=1;
			}
			start+=1;start2+=1;mid+=1;
		}
	}
}

void mergeSort(const void* a,int start,int end,comparator_t comp_func,swap_func_t swap_func){
	if(start>=end){
		return;
	}
	int mid = start + (end-start)/2;
	mergeSort(a,start,mid,comp_func,swap_func);
	mergeSort(a,mid+1,end,comp_func,swap_func);
	merger(a,start,mid,end,comp_func,swap_func);
}

void solve(){
	int nitems,total_cost,i,curr_cost;
	assert(fscanf(stdin,"%d %d",&nitems,&total_cost)>0);
	
	FOR(i,0,nitems){// cost
		assert(fscanf(stdin,"%d",&pairs[i].first)>0);
	}
	FOR(i,0,nitems){// number of pages
		assert(fscanf(stdin,"%d",&pairs[i].second)>0);
	}
	mergeSort(pairs,0,nitems-1,comparePII,swapPII); // sort by  NumberOfPages/Cost ratio
	memset(dp,0,sizeof(dp));
	
	FOR(i,0,nitems){
		/*filling should happen from last greatest cost */
		ROF(curr_cost,0,(total_cost+1)){	
							if(curr_cost>=pairs[i].first)
								dp[curr_cost] = max((dp[curr_cost]),(dp[curr_cost-pairs[i].first]+pairs[i].second));
			}
	}
	printf("\n%d%c",dp[total_cost],'\n');
}

int main(){
	int tt=1;
	//assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}

// https://atcoder.jp/contests/dp/tasks
//https://cses.fi/problemset/task/2183
