#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

long long int binpow(int base,int exponent){
	long long int res = 0;
	while(exponent>0){ // base = 4 , exponent = 15 = 2^0 + 2^1 + 2^2 + 2^3
		if(exponent&1) res += base; // res -> 4 + 4*4 + (4*4)*(4*4) + (4*4)*(4*4)*(4*4)
		base *= base;   // base exponentiation in parts
		exponent /= 2;  // discard last bit 
	}
	return res;
}
int mod = (int)1e9+7;
long long int pow2[1000001],pow3[1000001];
void init(){
	pow2[0]=1;pow3[0]=1;
	for(int i=1;i<1000001;i++){
		pow2[i] = 2*pow2[i-1]%mod;
		pow3[i] = 3*pow3[i-1]%mod;
	}
	return;
}

void solve(int n){
	long long int ans = pow2[n]*pow2[n] % mod;
	ans -= 2*pow3[n];
	while(ans<mod){
		ans += mod;
	}
	if(ans>=mod){
		ans %= mod;
	}
	ans += pow2[n];
	while(ans<mod){
		ans += mod;
	}
	if(ans>=mod){
		ans %= mod;
	}
	printf("%lld\n",ans);
	// Explanation for counting  list of possible numbers where A is not subset of B and 
	// B is not subset of A we need to use princple of inclusion and exclusion and remove pairs being subsets 
	// of either one of them ex.(2,7) 
	// total = (2^n)*(2^n)
	// pairs = 2*(3^n) why ? here arrangement/order is considered considered ex. (2,7) and(7,2) should be 		considered as separate one .so arrangement over choose. but for elements having same value we have removed them twice by doing this for example (2,2),(3,3),(7,7),etc.
	// we need to undo our removal by adding 2^n why we took or do everything in terms of 2^n as theere are all subsets of n . for example n=4 -> 1,2,3,4,5,6,....16(2^n)

	// total = 2^n*2^n - 2*3^n + 2^n 
	// total = AllPairs - AllPairsWithSubset + Putback  
	return;
}

int main(){
	init();
	int tt,n;
	assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		assert(fscanf(stdin,"%d",&n)>0);
		solve(n);
	}
}
