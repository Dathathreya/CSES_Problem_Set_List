#include <stdio.h>
#include <assert.h>
#include <string.h>

#define N (1<<19)+1
typedef long long int lli;
int sz = 0;

typedef struct treeNode{
    lli mxpref;
    lli mxsuf;
    lli mxSubArray;
    lli sum;
}tNode;

/*https://cses.fi/problemset/task/1190*/

tNode sgtree[N];

lli min(lli a,lli b){return (a>=b)?(b):(a); }
lli max(lli a,lli b){return (a<=b)?(b):(a); }

/*using inline,union,memory partition,typedef for function_types. randomization using sys\time.h header*/

void init(){
    memset(sgtree,0,sizeof(sgtree));
    return;
}

void update(int idx,int putValue){
    int Sz = (1<<sz);
    sgtree[idx+Sz-1].mxpref = max(0,putValue);
    sgtree[idx+Sz-1].mxsuf  = max(0,putValue);
    sgtree[idx+Sz-1].sum    = putValue;
    int currIdx = idx+Sz-1;
    currIdx = currIdx>>1;
    while(currIdx>=1){
        int leftChild = (currIdx<<1),rightChild = (currIdx<<1)+1;
        sgtree[currIdx].mxSubArray = sgtree[leftChild].mxsuf+sgtree[rightChild].mxpref;  
        sgtree[currIdx].mxpref = max(sgtree[leftChild].mxpref,sgtree[leftChild].sum+sgtree[rightChild].mxpref);  
        sgtree[currIdx].mxsuf = max(sgtree[rightChild].mxsuf,sgtree[leftChild].mxsuf+sgtree[rightChild].sum);  
        sgtree[currIdx].mxSubArray = max(sgtree[currIdx].mxpref,sgtree[currIdx].mxSubArray);
        sgtree[currIdx].mxSubArray = max(sgtree[currIdx].mxsuf,sgtree[currIdx].mxSubArray);
        sgtree[currIdx].sum =  sgtree[leftChild].sum+sgtree[rightChild].sum;
        sgtree[currIdx].mxSubArray = max(sgtree[currIdx].sum,sgtree[currIdx].mxSubArray);
        sgtree[currIdx].mxSubArray = max(sgtree[currIdx].mxSubArray,sgtree[leftChild].mxSubArray);
        sgtree[currIdx].mxSubArray = max(sgtree[currIdx].mxSubArray,sgtree[rightChild].mxSubArray);
        currIdx = currIdx>>1;
    } 
    return;
}
/*
mistakes made in last attempt 
1) Mistake in not considering the left , right leaf's maxiSumSubarray 
2) not fixing correct size for segment tree 
3) not knowing where to start filling leaf nodes for array starting from index
 for 10 we need to start from 16, */

void solve(){
    int n,q,i,x,idx;
    init();
    sz = 0;
    assert(fscanf(stdin,"%d%d",&n,&q)>0);
    while((1<<sz)<n){
        sz++;
    }
    for(i=0;i<n;i++){
       assert(fscanf(stdin,"%d",&x)>0);
       update(i+1,x);
    }
    for(i=0;i<q;i++){
        assert(fscanf(stdin,"%d%d",&idx,&x)>0);
        update(idx,x);
        printf("%lli\n",sgtree[1].mxSubArray);
    }
    return ; 
}

int main()
{
    int tt=1;
    while(tt--){
        solve();
    }
    return 0;
}
