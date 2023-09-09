#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <map>

#define N (int)1e9+7
#define max(a,b) (a>=b)?(a):(b)
using namespace std;

void solve()
{
    int n,x,i,first=0,last=0;
    int answer=0;
    assert(fscanf(stdin,"%d",&n)>0);
    map<int,int>a;
    //int a[N];
    int b[n];
    for(i=0;i<n;i++)
    {
        assert(fscanf(stdin,"%d",&x)>0);
        b[i]=x;
    }
    //i=0;
    for(;first<n;)
     {
        while(!a[b[last]] && last<n)
        {
            a[b[last]]+=1;     
            answer=max(answer,(last-first+1));
            last+=1;
        }
        a[b[first]]-=1;
        first+=1;
     }
     printf("%d\n",answer);   
     return; //break;continue;goto;void;
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