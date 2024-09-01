#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef long long int ll;

const ll mod = (int)1e9+7;
#define R (int)3e6+1
static void io_init() {
#ifdef  LocalStreetLampsLitOnFire
    assert(freopen("in.txt", "r", stdin) > 0);
    assert(freopen("a_out.txt", "w", stdout) > 0);
#endif //  LocalStreetLampsLitOnFire
}

ll fact[R];

// Multinomial Theorem 
// (x1+x2+x3+x4+x5+....+xk)^n = sum((nC(k1+k2+k3+...+kN<=n)) x1^k1.x2^k2.x3^k3.x4^k4....xkN^kN )

// Stars and Bars method 
// (x1+x2+x3+x4+....xk) = n where (x1,x2,x3,x4....xk>0) i.e. all must be atleast having one  as value
// Fix x1 x2 x3 x4 where x1 , x2 , x3 and x4 represents individual persons
// expand n as 1s 

// 1 1 1 1 1 1 1 1 1 1 1 1 1 
//  | | |         |
// for each person to atleast have 1 value we have a choice of k-1 from n-1 items 


// 1 1 1 1 1 1 1 1 1 1 1 1 1 
//                           | | | | | |       

/*

    First bar means how many undistingusihable items goes into my bin_2
    same for all bins till n 
    last bar means how many  undistingusihable items goes into my bin_1
    
*/  
// each person can have nothing as value we have a choice of k   from   (n-1)+k items 

void fill_fact(int mod){
    fact[0] = 1;
    for(ll i=1;i<R;i++){
        fact[i] = i*fact[i-1]%mod;
    }
    return;
}

ll bin_expo(ll base,ll exponent,ll mod){
    ll res = 1;
    while(exponent){
        if(exponent&1){
            res = res*base%mod;
        }
        base = base*base%mod;
        exponent >>= 1;
    }
    return res;
}

ll mod_inv(ll x,ll mod){
    if(x<=1) return x;
    return mod - mod/x*mod_inv(mod%x,mod)%mod;
}


ll nCr(ll n,ll r,ll m){
    ll nume = fact[n];
       // nume = nume*mod_inv(fact[n-r],mod)%mod;
       // nume = nume*mod_inv(fact[r],mod)%mod;
        nume = nume*bin_expo(fact[n-r],mod-2,mod)%mod;
        nume = nume*bin_expo(fact[r],mod-2,mod)%mod;
    return nume;
}

/*
  x x x x x x x x x x x x x 
|                           | | | | |     

// --- bin2 will be filled with all cnt(x) until previous bar 
--- bin3 willbe filled with all cnt(x) until previous bar 
....bin4 bin5 bin6 ....  bin7 
 in case of zero's we need to consider k bars , we need to pick k bars out of n-1+k items  
*/


void solve(){
    // Stars and Bars 
    int distinct,same;
    assert(fscanf(stdin,"%d%d",&distinct,&same)>0);
    printf("%lld\n",nCr(distinct+same-1,distinct-1,mod)); 
}

int main(){
    int  tt = 1;
    io_init();
    fill_fact(mod);
    // assert(fscanf(stdin,"%d",&tt)>0);
    while(tt--){
        solve();
    } 
}
