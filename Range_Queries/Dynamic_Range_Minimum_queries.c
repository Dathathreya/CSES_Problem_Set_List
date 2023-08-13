#include <stdio.h>

#define FOR(i,a,b) for(i=a;i<=b-1;i++)
#define min(a,b) (a>=b)?(b):(a)
#define max(a,b) (a<=b)?(b):(a)
#define inf (1ll<<62)
#define N 400010

typedef long long int lli;
lli tree[N];
int n;

void update(int idx,lli x)
{
	idx += n;
	tree[idx]=x; idx>>=1;
	while(idx>=1){		
		tree[idx] = min(tree[2*idx],tree[2*idx+1]);
		idx>>=1;
	}
	return;
}

lli query(int qbegin,int qend)
{
	qbegin +=n;qend +=n;
	lli s= inf,c;
	while(qbegin<=qend){
		if(qbegin&1) { s=min(s,tree[qbegin]); qbegin+=1;}
		if(~qend&1) {s=min(s,tree[qend]); qend-=1;}
		qend>>=1;qbegin>>=1;
	}
	return s; 
}

void solve()
{
	int q,i,T;
	lli x,a,k;
	fscanf(stdin,"%d %d",&n,&q);	
	
	FOR(i,0,n){
		scanf("%lli",&x);		
		update(i,x);
	}
	
	FOR(i,0,q){
		scanf("%d %lli %lli",&T,&a,&k);
		if(T==1){			
			update(a-1,k);
			
		}
		else{			
			printf("%lli\n",query(a-1,k-1));
		}
	}
	return;
}

int main(int argc,char* argv[])
{
	int tt;		
	tt=1;
	//printf("%lli\n",inf);
	while((tt--)>0)
	{		
		solve();
	}
}