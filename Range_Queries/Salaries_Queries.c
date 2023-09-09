#include <stdio.h>  //<cstdio>
#include <stdlib.h> //<cstdlib>
#include <assert.h> //<cassert>
#include <iostream>

typedef long long int lli;
#define N ((int)(4e6)+10)
#define inf ((lli)(1e16)+7)
#define FOR(i,a,n) for(i=a;i<=n-1;i++)
#define max(a,b) (a>=b)?(a):(b)
#define min(a,b) (a<=b)?(a):(b)

typedef struct pair{lli f;lli s;//int fi;int si;
int span;
}pii;

using namespace std;
int n;

pii tree[N];

void init(){
    int i;
    FOR(i,0,(N)){
    tree[i].f=inf;tree[i].s=0;//tree[i].fi=-1;tree[i].si=-1;
    tree[i].span=0;
    }
}

int  Log(int x){
    int k=1;
    while((1<<k)<x){
        k+=1;
    }
    return k;
}
void update(int i,lli x){
        i+=n;
        tree[i].f=x;
        tree[i].s=x;//tree[i].fi=i;tree[i].si=i;
        tree[i].span=1;
	    i>>=1;
        while(i>=1){
            int left=(2*i),right=2*i+1;
            tree[i].f = min((tree[left].f),(tree[right].f));
            tree[i].s = max((tree[left].s),(tree[right].s));
            tree[i].span = tree[left].span + tree[right].span;
	        i>>=1;
        }
}

int query(int A,int B,int root){
        if((root<(2*n))){
            if((tree[root].f>=A)&&(tree[root].s<=B)){
                return tree[root].span;
            }
            if((tree[root].s<A)||(tree[root].f>B)){
                return 0;
            }
            return (query(A,B,2*root))+(query(A,B,2*root+1));
        }
        return 0;
}

void solve(){
    
    int q,x,i,nn;
    assert(fscanf(stdin,"%d %d",&n,&q)>0);
    nn=n;n=(1<<(Log(n)));
    FOR(i,0,nn){
        //assert(fscanf(stdin,"%d",&x)>0);
        cin>>x;
        update(i,x);
    }
    // FOR(i,0,(2*n)){
    // printf("(%d %d %d)\n",tree[i].f,tree[i].s,tree[i].span);
    // }
    FOR(i,0,q){
        char c;
        lli A,B;
        //assert(fscanf(stdin,"%c",&c)>0);
        //fflush(stdin);
        //assert(fscanf(stdin,"%d %d",&A,&B)>0);
        cin>>c>>A>>B;
       // printf("%c %d %d\n",c,A,B);
        
        if(c=='?'){ // query
            printf("%i\n",query(A,B,1));
        }
        else{ // update
            update(A-1,B);
        }
    }
}

int main()
{
    init();
    int tt=1;
    //fprintf(stderr,"%d\t",N);
    //fprintf(stderr,"%d",inf);
    //assert(fscanf(stdin,"%d",&tt)>0);
    while((tt--)>0){
        solve();
    }
}
