#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef long long unsigned llu;
typedef long long  ll;
#define M (int)1e5+1
#define R (int)1e6+1

const ll MOD = (int)1e9 + 7;

ll fact[R], multiplicate_inverses[R];

/*
M = Q*N + R
M = (M/N)*N + (M%N)

upon taking modulus we remove M

0 ~ (M/N)*N + (M%N)

(M % N) = -((M / N) * N)
(1 / N) = 0 - ((M / N) * (1 / (M % N)))

inv(N)%MOD  = M - ((M/N)*inv(M%N))%MOD under mod and remove brackets
*/

static void io_init() {
#ifdef  LocalStreetLampsLitOnFire
    assert(freopen("in.txt", "r", stdin) > 0);
    assert(freopen("a_out.txt", "w", stdout) > 0);
#endif //  LocalStreetLampsLitOnFire
}

void fill_fact() {
    fact[0] = 1;
    for (int i = 1; i < R; i++) {
        fact[i] = i * fact[i - 1] % MOD;
    }
    return;
}

ll expo(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll multiplicativeInverse(int x, int mod) {
    if (x <= 1) return x;
    //if (x == -1) return 1;
    return mod - mod / x * multiplicativeInverse(mod % x, mod) % mod;
}

void find_all_multiplicative_inverses(int mod) {
    multiplicate_inverses[1] = 1;  // assume we already defined this array
    for (int i = 2; i < R; i++)
    {
        multiplicate_inverses[i] = mod - 1ll * (mod / i) * multiplicate_inverses[mod % i] % mod;
    }
    return;
}

// 7 = 2
// F(2) = 7 - (7/2)*m(7%2,7)
// f(2) = 7 - (3)*m(1,7)
// f(2) = 7 - 3*1 = 4 
// f(5) = 7 - 1*m(2,7) = 7-4 = 3
// f(2) = 4  

void solve() {
    int a, b;
    assert(scanf("%d%d", &a, &b) > 0);
    int nume = fact[a];
    int deno1 = fact[b];
    int deno2 = fact[a - b];
    // not handled
    //nume = nume * multiplicate_inverses[deno1] % MOD; // Runtime due to Memory Limit Exceeded Error
    //nume = nume * multiplicate_inverses[deno2] % MOD;// Runtime due to Memory Limit Exceeded Error
    nume = nume * multiplicativeInverse(deno1, MOD) % MOD;
    nume = nume * multiplicativeInverse(deno2, MOD) % MOD;
    printf("%d\n", nume);
}

int main()
{
    int tt = 1;
    io_init();
    fill_fact();
    find_all_multiplicative_inverses(MOD);
    assert(fscanf(stdin, "%d", &tt) > 0);
    while (tt--) {
        solve();
    }
    return 0;
}
