#include <stdio.h>
#include <assert.h>

typedef long long int ll;
ll a,b,c;
#define MX (int)1e6+7
const ll mod=(ll)1e9+7;
ll psv[MX];
ll power(ll base,ll pow,ll mod)
{
    if(pow==0){ return 1;}
    ll ret = power(base,pow/2,mod);
    ret%=mod;
    ret*=ret;
    ret%=mod;
    if(pow&1) {ret*=base;ret%=mod;}
    return ret;
}
ll extended_euclidean(ll* x,ll* y,ll a,ll b)
{
    // recursive function 
    if(a==0){
        *x=1;*y=0;
        return b;
    }
    ll x1,y1;
    ll gcd=extended_euclidean(&x1,&y1,b%a,a); //(x%m+m)%m
    *x= (y1-(b/a)*x1);
    *y= (x1);
    return gcd;
}

ll inverse(ll a,ll mod){
    return (a<=1)?(a):(mod-(ll)(mod/a)*inverse(mod%a,mod)%mod);
}
ll* pcmp_inverse(int size)
{
    ll inv[size];
    inv[1]=1;
    for(int i=2;i<size;i++){
        inv[i]= mod - (ll)(mod/a)*inv[mod%a]%mod;
    }
    return inv;
}

ll* invs(ll *a,int sz){
    ll v=1,b[sz];
    int i=0;
    for(i=0;i<sz;i++){
        b[i]=v;
        v = v * a[i] % mod; // prefix product array precomputed
    }
    ll x,y;
    /*ll gcd=*/extended_euclidean(&x,&y,v,mod);
    x=(x%mod+mod)%mod;
    for(i=sz-1;i>=0;i--){
        b[i] = b[i] * x % mod ; // total_inv is x * precomputed prefix and suffix  
        x = x * a[i] %mod;   // x is product of inverse(x1....xn) and  suffix product
    }
    return b;
}

void psf(ll sz){
    for(ll i=1;i<=sz;i++){
        psv[i]=i;
    }
    for(ll i=2;i*i<=sz;i+=1)
    {
        // smallest divisor reachable for current no.
        if(psv[i]==i)
        {
            for(ll p=i*i;p<=sz;p+=i)
            {
                if(psv[p]==p) psv[p]=i;
            }
        }
    }
}

ll getCountOfDivisors(ll num){
    int cnt=1,answer=1;
    while(num!=1)
    {
        cnt=1;
        ll smallest=psv[num];
        while(num%smallest==0)
        {
            cnt+=1;
            num/=smallest;
        }
        answer*=cnt;
    }
    return answer;
}
void solve()
{
    assert(scanf("%lli",&a)>0);
    printf("%lli ",getCountOfDivisors(a));
}
int main()
{
    int tt;
    assert(scanf("%d",&tt)>0);
    psf(MX-1);
    while((tt--)>0)
    {
        solve();
    }
}