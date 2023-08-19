#include <stdio.h>
#include <assert.h>

#define FOR(i,a,n) for(i=a;i<=n-1;i++)
typedef struct pair{ int f;int s; } pii;
void swap(pii* a,pii *b)
{
pii t=*a;*a=*b;*b=t;
}
void heapify(pii* a,int root,int n)
{
	// https://github.com/Dathathreya/CSES_Problem_Set_List.git
	int largest,left,right;
	left=(root<<1)+1;
	right=(root<<1)+2;
	largest=root;  	
	if(left<n && a[largest].s<a[left].s){
		largest=left;
	}
	if(right<n && a[largest].s<a[right].s){
		largest=right;
	}
	if(largest!=root)
	{
		swap(&a[root],&a[largest]);
	        heapify(a,largest,n);	
	}
}
void heapSort(pii* a,int n)
{
int i;
for(i=n/2-1;i>=0;i--)
{
heapify(a,i,n);
}
for(i=n-1;i>=0;i--)
{
swap(&a[i],&a[0]);
heapify(a,0,i);
}
}

void solve(){
	int n,begin,end,ans=1,i;
	assert(scanf("%d",&n)>0);	
        pii a[n];	
	FOR(i,0,n)
	{
		assert(scanf("%d %d",&begin,&end)>0);				
		a[i].f=begin;a[i].s=end;
	}
	heapSort(a,n);
	end=a[0].s;
	for(i=0;i<=n-1;i++)
	{
           if(a[i].f>=end)		
	   {
		ans += 1;
		end = a[i].s;
	   }	   
	}
	printf("%d\n",ans);	
}	
int main()
{
   int tt=1;
  // assert(scanf("%d",&tt)>0);
   while((tt--)>0){
	solve();	   
   }	   
}
