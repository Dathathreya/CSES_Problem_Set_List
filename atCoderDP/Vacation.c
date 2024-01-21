#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define N (int)2e5+4
#define min(a,b) (a<=b)?(a):(b)
#define max(a,b) (a>b)?(a):(b)
typedef long long int lli; 
lli act[3];

enum Act{
    A_1=0,B_1=1,C_1=2
};

void solve(){
    int n,i,A,B,C;
    assert(fscanf(stdin,"%d",&n)>0);
    memset(act,0,sizeof(act));
    
    assert(fscanf(stdin,"%d %d %d",&act[A_1],&act[B_1],&act[C_1])>0);
    for(i=1;i<n;i++){
        assert(fscanf(stdin,"%d %d %d",&A,&B,&C)>0);
        lli a1=act[A_1],b1=act[B_1],c1=act[C_1];

        // person ends day with act C 
        act[C_1] = max((a1+C),(b1+C));
        // person ends day with act B
        act[B_1] = max((a1+B),(c1+B));     
        // person ends day with act A
        act[A_1] = max((b1+A),(c1+A));     
    }
    lli ans= max(act[A_1],act[B_1]);
    printf("%lli\n",max(ans,(act[C_1])));
}

int main(){
    int tt=1;
    // assert(fscanf(stdin,"%d",&tt)>0);
    while(tt--)
        solve();
}
