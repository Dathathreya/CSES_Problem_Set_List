#include <stdio.h>
#include <assert.h>

#define FOR(i,a,n) for(i=a;i<=n-1;i++)
#define max(a,b) (a>=b)?(a):(b)
#define min(a,b) (a<=b)?(a):(b)
typedef struct pair{ int f;int s; } pii;

void swap(pii* a,pii *b)
{
pii t=*a;*a=*b;*b=t;
}
void heapify(pii* a,int root,int n)
{
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
	int n,b,x,i;
	assert(scanf("%d %d",&n,&x)>0);	
    pii a[n];	
	FOR(i,0,n)
	{
		assert(scanf("%d",&b)>0);				
		a[i].f=(i+1);
	    a[i].s=b;
	}
	heapSort(a,n);
	int l=0,r=n-1;
    if(n==1) {printf("IMPOSSIBLE\n");return;}
	while(l<r)
	{
    		if(a[r].s<x){
			    if(a[l].s+a[r].s==x){
                    //got=true;
                    printf("%d %d\n",a[l].f,a[r].f);
		    return; // break;
			    }
		        else 
			    {
				    if((x-a[r].s)>a[l].s) l+=1; // want more move towards right 
				    else r-=1;
			    }	
		}
		else{
		    r -= 1;	
		}	
	}
        printf("IMPOSSIBLE\n");
     return;   
}	
int main()
{
   int tt=1;
  // assert(scanf("%d",&tt)>0);
   while((tt--)>0){
	solve();	   
   }	   
}
