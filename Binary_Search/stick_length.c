#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

#define N (int)1e6+1
#define min(a,b) (a<=b)?(a):(b)
typedef long long int lld;

void merger(lld* a,int low,int mid,int high)
{
int n=mid-low+1,m=high-mid,i,j,k;
int L[n],R[m];
for(i=low;i<=mid;i++)
{
L[i-low]=a[i];		
}
for(i=mid+1;i<=high;i++)
{
R[i-(mid+1)]=a[i];		
}
i=0;j=0;k=low;
while((i<n)&&(j<m)){
	if(L[i]<=R[j]){
	    a[k]=L[i];
	    i++;k++;		    
	}
	else{
	    a[k]=R[j];
	    j++;k++;		    
	}
}
while(i<n)
{
   a[k++]=L[i++];		
}
while(j<m)
{ 
  a[k++]=R[j++];
}
return;
}

void mergeSort(lld* a,int low,int high){
if(low>=high) return;

int mid=low+((high-low)>>1);
mergeSort(a,low,mid);
mergeSort(a,mid+1,high);
merger(a,low,mid,high);

}
void sort(lld* a,int n)
{
// divide and conquer
mergeSort(a,0,n-1);		
}

void solve(){
int n,i,j;
lld x;
assert(fscanf(stdin,"%d",&n)>0);
lld a[N+1];
memset(a,0,sizeof(a));
for(i=0;i<=n-1;i++)
{
assert(fscanf(stdin,"%lld",&x)>0);
a[x]+=1;
}
for(i=N;i>=1;i--)
{
int cnt=0;
for(j=i;j<=N;j+=i)
{
    cnt+=a[j];	
}
if(cnt>=2)
{
   printf("%i\n",i);
  break;   
}
}

}
 
int main()
{
	int tt=1;
	while((tt--)>0){
		solve();
	}
}
