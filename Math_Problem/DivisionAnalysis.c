#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



typedef long long unsigned llu;
typedef long long  ll;
#define M (int)1e5+1

const ll MOD = 1e9 + 7;

int prime[100001][2];


static void io_init() {
#ifdef  LocalStreetLampsLitOnFire
    assert(freopen("in.txt", "r", stdin) > 0);
    assert(freopen("a_out.txt", "w", stdout) > 0);
#endif //  LocalStreetLampsLitOnFire
}

ll expo(ll a,ll b){
    ll res = 1;
    while(b){
        if(b&1){
            res = res*a%MOD; 
        }
        a = a*a%MOD; 
        b >>= 1;       
    }
    return res;
}

void solve() {
    int n;
    ll count_divisors = 1, sum_of_divisors = 1 , prod_of_divisors = 1 , count_divisors2 = 1;
    assert(scanf("%d", &n) > 0);
    count_divisors = 1;
    for (int i2 = 0; i2 < n; i2++) {  
        assert(scanf("%d%d", &prime[i2][0], &prime[i2][1]) > 0); 
    }
   ll div_cnt = 1, div_sum = 1, div_prod = 1, div_cnt2 = 1;
   for (int i = 0; i < n; i++) {
        div_cnt = div_cnt*(prime[i][1]+1)%MOD;
        div_sum = div_sum*(expo(prime[i][0],prime[i][1]+1)-1)%MOD*expo(prime[i][0]-1,MOD-2)%MOD;

        // anyone of ints should be long long otherwise mul wont work 


        div_prod = expo(div_prod,prime[i][1]+1)%MOD*expo(expo(prime[i][0],(1ll*prime[i][1]*(prime[i][1]+1))/2),div_cnt2)%MOD;
        // prev_divs will get repeated themselves (K+1) times 
        // current total combinations of prime P will repeat Ci-1 times 
        // result is product of them 
        // MOD should be MOD-1 for counting before doing mul by fermat theorem 
        // we consider MOD-1 as A^(B) !~ A^(B mod MOD) mod MOD
        // but A^(B) ~ A^(B mod MOD-1) mod (MOD-1)
        div_cnt2 = div_cnt2*(prime[i][1]+1)%(MOD-1);
   }
   printf("%lld %lld %lld\n", div_cnt, div_sum, div_prod);
}



int main()
{
    int tt = 1;
    io_init();
    //assert(fscanf(stdin,"%d",&tt)>0);    
    while (tt--) {
        solve();
    }
    return 0;
}

