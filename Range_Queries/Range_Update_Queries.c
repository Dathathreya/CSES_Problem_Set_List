#include <stdio.h>
#include <string.h>
//C:\Users\d.pasupathi\Documents\Practice\cpp_Files\Git_repo\CSES_Problem_Set_List\Range_Queries
#define FOR(i,a,b) for(i=a;i<=b-1;i++)
#define min(a,b) (a>=b)?(b):(a)
#define max(a,b) (a<=b)?(b):(a)
#define inf (1ll<<62)
#define N 400010
typedef unsigned long long  llu;
#define mod (lli)((1e18)+7)

llu tree[N];
int n;

void init()
{
	memset(tree,0,N*sizeof(llu));
	return;
}

llu query(int pos){
	pos += n;
	llu s=0llu;
	while(pos>=1){		
		s+=tree[pos];
		pos >>= 1;
	}	
	return s;
}

void update(int qBegin,int qEnd,llu nm){
	qBegin += n; qEnd += n;
	while(qBegin <= qEnd)
	{
		if(qBegin&1){ tree[qBegin] += nm; qBegin+=1;}
		if(~qEnd&1){ tree[qEnd] += nm; qEnd-=1;}
		qBegin>>=1;
		qEnd>>=1;
	}
	return;
}

void solve()
{
	init();
	int q,i,T,k,a,b;
	llu x,u;
	fscanf(stdin,"%d %d",&n,&q);	
	
	FOR(i,0,n){
		scanf("%llu",&x);		
		update(i,i,x);
	}	
	FOR(i,0,q){		
		scanf("%d",&T);
		if(T==2){			
			scanf("%d",&k);
			printf("%llu\n",query(k-1));			
		}
		else{			
			scanf("%d %d %llu",&a,&b,&u);
			update(a-1,b-1,u);
		}
	}
	return;
}

int main(int argc,char* argv[])
{
	int tt;		
	tt=1;
	//fprintf(stderr,"%llu\n",mod);
	while((tt--)>0)
	{		
		
		solve();
	}
}