#include <stdio.h>
#include <inttypes.h>
#include <limits.h>
#include <assert.h>

#define FOR(i,a,n) for(i=a;i<=n-1;i++)
#define max(a,b) (a>=b)?(a):(b)
typedef unsigned long long llu; 
typedef long long int lli;

void swap(int *a,int *b){
    int t=*a;*a=*b;*b=t;
}
void heapify(int* a,int root,int n){
    int largest,left,right;
    largest=root;
    left=(root<<1)+1,right=(root<<1)+2;
    if(left<n && a[largest]<a[left]){
        largest=left;
    }
    if(right<n && a[largest]<a[right]){
        largest=right;
    }
    if(largest!=root){
        swap(&a[largest],&a[root]);
        heapify(a,largest,n);
    }
}
void heapSort(int* a,int n){
    int i;
    for(i=n/2-1;i>=0;i--){
        heapify(a,i,n);
    }
    for(i=n-1;i>=0;i--){
        swap(&a[0],&a[i]);
        heapify(a,0,i);
    }
}

void solve()
{
    int n,i,came,left,mx=INT_MIN,cnt=0;
    assert(scanf("%d",&n)>0);
    int arrival[n],departure[n];
    for(i=0;i<=n-1;i++)
    {
        assert(scanf("%d %d",&came,&left)>0);
        arrival[i]=came;departure[i]=left;
      //  printf("%d %d\n",arrival[i],departure[i]);
    }
    came=0,left=0;
    heapSort(arrival,n);
    heapSort(departure,n);
    while(came<n)
    {
        if(arrival[came]<departure[left]){
            cnt+=1;came+=1;
        }        
        else {
            cnt-=1;left+=1;
        }
        mx = max(cnt,mx);            
    }
    printf("%d\n",mx);
}

int main()
{
    int tt;
    tt=1;
    //assert(fscanf(stdin,"%d",&tt)>0);
    while((tt--)>0)
    {
        solve();
    }
}
