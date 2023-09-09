#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N (int)4e5+10
#define max(a,b) (a>=b)?(a):(b)
//using namespace std;
typedef long long int lli;
typedef struct pair{ lli totalSum,prefixSum; }pii;

int n;
pii tree[N+1];

void fill()
{
    for(int i=0;i<=N;i++)
    {
        tree[i].totalSum=0;
        tree[i].prefixSum=0;
    } 
    return;
}

void update(int idx,lli v)
{
    idx+=n;
    tree[idx].totalSum=v;
    tree[idx].prefixSum=v;
    idx>>=1;
    while(idx>=1){
    tree[idx].totalSum = tree[2*idx].totalSum + tree[2*idx+1].totalSum;
    tree[idx].prefixSum = max((tree[2*idx].prefixSum),(tree[2*idx].totalSum)+(tree[2*idx+1].prefixSum));
    idx>>=1;    
    }
    return;
}

void solve()
{
    
}

int main()
{
    int tt=1;
    fill();
    //assert(fscanf(stdin,"%d",&tt)>0);
    while((tt--)>0)
    {
        //int n=10;
        solve();
    }
}