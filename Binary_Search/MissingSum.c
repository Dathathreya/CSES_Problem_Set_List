#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

typedef int (*compfn_t)(const void* arr,const void* brr,int f,int s,int IsLesserOrEqual);
typedef void (*swapfn_t)(const void* arr,const void* brr,int f,int s);
int n;

int compareInt(const void* arr,const void* brr,int f,int s,int IsLesserOrEqual){
	int* temp_a=(int*)arr;
	int* temp_b=(int*)brr;
	if(IsLesserOrEqual)
		return temp_a[f]<=temp_a[s];
	return temp_a[f] < temp_a[s];
}

void swapInt(const void* arr,const void* brr,int f,int s){
	int* temp_a=(int*)arr;
	int* temp_b=(int*)brr;
	int c = temp_a[f];
	temp_a[f]=temp_a[s];
	temp_a[s]=c;
	return;
}

void merger(const void* arr,int start,int mid,int end,compfn_t compfn,swapfn_t swapfn){
	int start2=mid+1;
	if(compfn(arr,NULL,mid,start2,1)){
		return;
	}

	for(;(start<=mid)&&(start2<=end);){
		if(compfn(arr,NULL,start,start2,1)){
			start+=1;
		}
		else{
			int low = start2,high = end,ans=end;

			// complete binary search -> upper_bound(<=),lower_bound(<)

			while(low<=high){
				int m = low+(high-low)/2;
				if(compfn(arr,NULL,m,start,0)){
					low = m+1;		
				}
				else{
					ans = m;
					high = m-1;
				}
			}

			int fr=start,sc=start+1;
			while(1){
				if(fr>=start2){ // swap till it hits
					break;
				}
				swapfn(arr,NULL,fr,sc);
				fr+=1;sc+=1;
			}
			
			while((fr<=end)&&(sc<=end)){
				if(compfn(arr,NULL,fr,sc,1)){ // placed at correct spot
					break;
				}
				swapfn(arr,NULL,fr,sc);
				fr+=1;sc+=1;
			}
			mid=mid-1;
			start2=mid+1;
		}
	}	

	return;
}

void mergeSort(const void* arr,int start,int end,compfn_t compfn,swapfn_t swapfn){
	if(start>=end){
		return;
	}
	int mid = (end+start)/2;
	mergeSort(arr,start,mid,compfn,swapfn);
	mergeSort(arr,mid+1,end,compfn,swapfn);
	merger(arr,start,mid,end,compfn,swapfn);
}

// sort numbers to get order 
// if prefix_sum+1 uptill current lesser than current array element 
// prefix_sum+1 is unreachable as current_Array_Element with atleast 1 is still larger than prefix_Sum+1 

void solve(){
	int i;
	assert(fscanf(stdin,"%d",&n)>0);
	int a[n];
	
	long long unsigned prefix[n];
	
	for(i=0;i<n;i++){
		assert(fscanf(stdin,"%d",&a[i])>0);		
	}
	mergeSort(a,0,n-1,compareInt,swapInt);
	memset(prefix,0,sizeof(prefix));
	int found=0;
	long long unsigned curr=0;
	for(i=0;i<n;i++){
		
		if(curr+1<a[i]){
			printf("%llu\n",curr+1);found=1;break;
		}

		if(i==0)
			prefix[i]=a[i];
		else
			prefix[i]  = (a[i]+prefix[i-1]);
		curr=prefix[i];
		
	}
	if(!found)
   		printf("%llu\n",prefix[n-1]+1);
}

int main(int argc, char const *argv[])
{
	int tt=1;
	//assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
	return 0;
}

// floor division in python
// trunc division in c/cpp  
//a=-7,b=-5 -> -7-(-5)*(trunc(-7/-5))=-7+5*(trunc(1.4)) = -7+5*(1)=-2
//a=-7,b=5 -> -7-(5)*(trunc(-7/5))=-7-5*(trunc(-1.4)) = -7-5*(-1)=-2
//a=7,b=-5 -> 7-(-5)*(trunc(7/-5))=7+5*(trunc(-1.4)) = 7+5*(-1)=2
