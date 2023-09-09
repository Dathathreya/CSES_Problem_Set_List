#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define N (2000007)
#define max(a,b) (a>=b)?(a):(b)
#define min(a,b) (a<=b)?(a):(b)
int n;
int tree[(2*N)];

int Log(int x){int k=0;while((1<<k)<x){k+=1;}return k;}

void update(int i,int x)
{
i+=n;
tree[i]=x;
i/=2;
while(i>=1){
    tree[i]=max((tree[(2*i)]),(tree[(2*i)+1]));
    i /= 2;
}
return;
}

int query(int x){
    if(tree[1]<x) return -1;
    int k=1;
    while(k<n){
        int left,right;
        left=(2*k);
        right=(2*k)+1;
        if(tree[2*k]>=x){
            k=left; // go left
        }
        else{
            k=right; // go right
        }
    }
    return k-n;
}

void solve()
{
memset(tree,0,2*N*sizeof(int));
int x,i,q,nn,d;
assert(scanf("%d %d",&n,&q)>0);
nn=n;
n=(1<<Log(n));
fprintf(stderr,"%d\n",n);
for(i=0;i<=nn-1;i++)
{
 assert(fscanf(stdin,"%d",&x)>0);
 update(i,x);
}

for(i=0;i<=q-1;i++)
{
 assert(fscanf(stdin,"%d",&x)>0);
 int pos=query(x);
 printf("%d\t",pos+1);
 if(pos>=0){
     update(pos,tree[pos+n]-x);
 }   
}


}

int main()
{
int tt=1;
//assert(fscanf(stdin,"%d",&tt)>0);
while((tt--)>0)
{
solve();
}
}
