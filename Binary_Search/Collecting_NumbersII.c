#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define FOR(i,a,b) for(i=a;i<=n-1;i++)
#define N (int)2e5
typedef struct pair{int f;int s;}pii;

void merge(pii* a,int l,int M,int r)
{
int n=M-l+1,m=r-M,i=0,j=0,k=l;
pii L[n],R[m];
FOR(i,low,(mid+1)) L[i-low]=a[i];

FOR(i,(mid+1),(high+1)) R[i-(mid+1)]=a[i];

i=0;
while((i<n)&&(j<m)){
if(L[i].f<R[j].f){
a[k++/*starts with low*/]=L[i++];
}
else{
a[k++/*starts with low*/]=R[j++];
}
}
while(i<n){
a[k++]=L[i++]
}
while(j<m){
a[k++]=R[j++]
}
return;
}

void sort(pii*a,int l,int r)
{
	if(l>=r) return;
	int m=l+(r-l)>>1;
	sort(a,l,m); /*low to mid inclusive*/
	sort(a,m+1,r); /*mid+1 to high inclusive*/
	merge(a,l,m,r);
}

void solve()
{
int n,x,m;
assert(fscanf(stdin,"%d %d",&n,&m)>0);
pii a[n+1];
a[0].f=-1;
a[0].s=-1;
FOR(i,0,n)
{
assert(fscanf(stdin,"%d",&x)>0);
a[i+1].f=x;
a[i+1].s=i;
}

FOR(i,0,m)
{
int A,B;
assert(fscanf(stdin,"%d %d",&A,&B)>0);
int T=a[A-1].f;
a[A-1].f=a[B-1].f;
a[B-1].f=T;
sort(a,0,n);
int cnt=0;
FOR(i,1,(n+1))
{
    if(a[i].s>a[i-1].s){
    }
    else {
    cnt+=1;
    }    
}
printf("%lld\n",cnt+1);
}
return;
}

int main()
{
int tt=1;
// assert(fscanf(stdin,"%d",&tt)>0);
while((tt--)>0)
{
solve();
}
}
