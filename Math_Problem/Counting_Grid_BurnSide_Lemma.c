#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
 
typedef long long int ll;
typedef long long unsigned llu;
 
const ll mod = (int)1e9+7;
#define R (int)3e6+1
static void io_init() {
#ifdef  LocalStreetLampsLitOnFire
    assert(freopen("in.txt", "r", stdin) > 0);
    assert(freopen("a_out.txt", "w", stdout) > 0);
#endif //  LocalStreetLampsLitOnFire
}
 
// https://www-igm.univ-mlv.fr/~lecroq/string/node14.html#SECTION00140
 
// // https://www-igm.univ-mlv.fr/~lecroq/string/node14.html#SECTION00140
 
ll fact[R],dearr[R];
 
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
 
void fill_dearrangement(int mod){
    dearr[0] = 0; dearr[1] = 0;dearr[2] = 1;
    for(int i=3;i<R;i++){
        dearr[i] = (i-1)*(dearr[i-1]+dearr[i-2])%mod; // (9+2)*4
    }
    return;
}
 
int fixExponent(int a1,int b1,int M){
    // a1 %= M;
    // b1 %= M;
    // while(a1>(M/b1)){
    //     printf("%d %d",a1,M/b1);
    //     a1 = M - a1;
    // }
    // 493827160
    long long unsigned product = 1ll*a1*b1;
    // printf("%llu %llu\n",product,product%M);
    product %= M;    
    return product;
}
 
void solve(){
    // Stars and Bars 
    // Dearrangement of numbers using venn diagram and generalization
    // 3 person with arrangement of 3 gifts with each person having different 
    // n! - nC1*((n-1)!) + nC2*((n-2)!) - nC3*((n-3)!) + .... 
    // 4! - 4*3! + 4C2*(2!) - 4C3*(1!) + 4C4*(0!)
    // 5! - 5*4! + 5C2*(3!) - 5C3*(2!) + 5C4*(1!) - 5C5*(1!)
    // 0 + 10*6 - 10*2 + 5 - 1
    // 44 ? 
    // 0 + 12 - 4 + 1 = 9
    // 1 2 3 , all possible combination then consider one being fixed and remove twice put back one so on
    // it includes everything 
    // pick one record that has same gift to same person
    // D(5) = 5!*(1-1/1+1/2!-1/3!) + (5-1)
    // D(5) = (5-1)*((3!+4!)*(1-1/1+1/2!-1/3!) + 1 )
    // D(4) + D(3) = 30*(1-1/1+1/2!-1/3!) + 1
    // d(5) = (n-1)*(d(4)+d(3))
    // d(n) = (n-1)*(d(n-1)+d(n-2))
    int n;
    assert(fscanf(stdin,"%d",&n)>0);
    if(n%2==0){
        //ll ans =  
        ll ans = bin_expo(2,fixExponent(n,n,mod-1),mod)%mod; // 0-degree
        ans = ans+bin_expo(2, fixExponent(n/2,n/2,mod-1),mod)%mod;// 90-degree
        ans = ans+bin_expo(2, fixExponent(n,n/2,mod-1),mod)%mod;// 180-degree
        ans = ans+bin_expo(2, fixExponent(n/2,n/2,mod-1),mod)%mod;// 270-degree
        ans = ans*bin_expo(4,mod-2,mod)%mod;// 270-degree
        printf("%lld\n",ans);
    }
    else{
        //ll ans =  
        ll ans = bin_expo(2,fixExponent(n,n,mod-1),mod)%mod; // 0-degree
        ans = ans+2*bin_expo(2, fixExponent((n-1)/2,(n+1)/2,mod-1),mod)%mod;// 90-degree
        ans = ans+2*bin_expo(2, fixExponent((n-1)/1,(n+1)/2,mod-1),mod)%mod;// 180-degree
        ans = ans+2*bin_expo(2, fixExponent((n-1)/2,(n+1)/2,mod-1),mod)%mod;// 270-degree
        // forgot to put center cell can take two colours 
        ans = ans*bin_expo(4,mod-2,mod)%mod;// 270-degree
        printf("%lld\n",ans);
    }
    // TLE ? state transition with dp ?
    return;
}
 
int main(){
    int  tt = 1;
    io_init();
    fill_fact(mod);
    //fill_dearrangement(mod);
    // assert(fscanf(stdin,"%d",&tt)>0);
    while(tt--){
        solve();
    } 
}
// https://www.hackerearth.com/blog/developers/how-to-find-the-day-of-a-week/
// Determination of day of week 
// some math 
// probability
// string + geometry + algebra ?
//  31 91 31 31 30 31 
//  4*31 + 30 + 91 
//  174 + 30 
// Normal Year,sequence,prefixSumUnderModulo
// 31 28 31 30 31 30 31 31 30 31 30 31
//31 59 90 120 151 181 212 243 273 304 334 365 
// J  F  Ma Ap My Ju Jl Au Se Oc No De 
//  April July 
// 
// 3,3,6,1,5,6,2,6,0,6,6,1
// 3,0,3,2,3,2,3,3,2,3,2,3
// 3                                              
// J  F  M  A  M  J  J  A  S  O  N  D
// Leap Year
// 31 29 31 30 31 30 31 31 30 31 30 31
// J  F  M  A  M  J  J  A  S  O  N  D 
 
// April - July always starts on same date 
//
 
// D(1) = 0;
// D(2) = 1;
//1 2 
//2 1
// (n-1)*(D(n-1)+D(n-2))
//1 2 3
//3 1 2
//2 3 1
//  
