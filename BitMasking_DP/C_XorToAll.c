//Xor Problem 
//https://atcoder.jp/contests/arc135/tasks/arc135_c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define FOR(i,a,n) for(i=a;i<n;i++)
#define max(a,b) (a>=b)?(a):(b)
#define min(a,b) (a<=b)?(a):(b)
typedef unsigned long long  lli;

lli Log(lli n)
{
    if(n<=1) return 0;
    return 1+Log(n/2);
}

void solve(){
    int n,i,j,mx=0;
    assert(fscanf(stdin,"%d",&n)>0);
    lli a[n],sum=0,msb=0;
    FOR(i,0,n){
        assert(fscanf(stdin,"%llu",&a[i])>0);
        sum+=a[i];
        mx=max((a[i]),mx);
        if(mx==a[i]){
            msb=Log(mx);
        }
    }
    int ones[msb+1];
    memset(ones,0,sizeof(ones));
    FOR(i,0,n){
      for(j=0;j<=msb;j++)
      {
         if((1<<j)&a[i]){
             ones[j]+=1;
         }
      }
    }
    FOR(i,0,n)
    {
      lli sm=0;
      for(j=0;j<=msb;j++)
      {
          if(a[i]&(1<<j)){
            // use countOfOne with position of set  
            sm+=1llu*(n-ones[j])*(1<<j);     
          }
          else {
            // use countOfOne with position of unset
             sm+=1llu*(ones[j])*(1<<j);      
          }
      }
      sum=max(sum,sm);
    }
    fprintf(stdout,"%llu\n",sum);
}

int main(int argv,char *argc[]){
    int tt=1;   
    // assert(fscanf(stdin,"%d",&tt)>0);
    while((tt--)>0){
        solve();
    }
}