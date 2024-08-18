#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
// #include <sys\time.h>

#define __USE_MINGW_ANSI_STDIO 0

#define N (int)3e5+7
typedef long double ld;
typedef long long ll;
typedef long long unsigned llu;

// // #define N	2000
// #define N_	((N + 1) * (N + 1))
 
// unsigned int Z;
 
// int rand_() {
// 	return (Z *= 3) >> 1;
// }
 
// void srand_() {
// 	struct timeval tv;
 
// 	gettimeofday(&tv, NULL);
// 	Z = tv.tv_sec ^ tv.tv_usec | 1;
// }
 
// void sort(int *xx, int l, int r) {
// 	while (l < r) {
// 		int i = l, j = l, k = r, x = xx[l + rand_() % (r - l)], tmp;
 
// 		while (j < k)
// 			if (xx[j] == x)
// 				j++;
// 			else if (xx[j] < x) {
// 				tmp = xx[i], xx[i] = xx[j], xx[j] = tmp;
// 				i++, j++;
// 			} else {
// 				k--;
// 				tmp = xx[j], xx[j] = xx[k], xx[k] = tmp;
// 			}
// 		sort(xx, l, i);
// 		l = k;
// 	}
// }

// void swap(void* t1,void* t2,void* tmp,size_t pSize){
// 	memcpy(tmp,t1,pSize);
// 	memcpy(t1,t2,pSize);
// 	memcpy(t2,tmp,pSize);
// 	return;
// } 

int binPow(int base,int exponent,int mod){
	int res = 1;
	while(exponent){
		if(exponent&1) {
						res = ((res%mod)*(base%mod))%mod;
						if(res<=0) res+=mod;
						if(res>=mod) res-=mod;
						}
		base = ((base%mod)*(base%mod))%mod;
		if(base<=0) base+=mod;
		if(base>=mod) base-=mod;
		exponent >>= 1;
	}
	return res;
}

llu binPowM(llu base,llu exponent){
	llu res = 1llu;
	while(exponent){
		if(exponent&1){
			res *= base;
		}
		base *= base;
		exponent >>= 1;
	}
	return res;
}

int lastThreeDigits(int base,int exponent){
	int res = 1;
	base %= 1000L;
	while(exponent){
		if(exponent%2) res = (res*base)%1000L;
		base = (base*base)%1000L;
		exponent >>= 1L;
	}
	return res;
}

void printfirst3_last3(int base,int exponent){
	ld expo1 = (ld)exponent*log10(base);
	int first3digits = pow(10,expo1-floor(expo1))*100;
	printf("%d...%d\n",first3digits,lastThreeDigits(base,exponent));
}

int a[N],newSequence[N],permutation[N];

void fill_perm(int n){
	for(int i=0;i<n;i++){
		a[i] = (i+1);
		if(i<n/2){
			permutation[i] = 2*i; 
		}
		else if((n%2==1)&(i==(n/2))){ permutation[i] = 2*i; }
		else  permutation[i] = 2*i - 2*(n/2-(n%2==0)) - 1;
	}
	return;
}

void permutate(int n,bool selfApply){
	for(int i=0;i<n;i++){
		newSequence[i] = (selfApply)?(a[permutation[i]]):(permutation[permutation[i]]);
	}
	for(int i=0;i<n;i++){
		if(selfApply){
			a[i] = newSequence[i];
		}
		else {
			permutation[i] = newSequence[i];
		}
	}
	return;
}

void binaryExponentiation(int n,int exp){
	while(exp){
		if(exp&1){
			permutate(n,true);
		}
		permutate(n,false);
		exp >>= 1;
	}
	return;
}

void chef_and_riffles(int n,int repeat){
	fill_perm(n);
	binaryExponentiation(n,repeat);
	for(int i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
}

void solve(){
	int n,repeat;
	assert(fscanf(stdin,"%d%d",&n,&repeat)>0);
	chef_and_riffles(n,repeat);	
}

int main(int argc,char* argv[]){
	int tt=1;
	assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}

// 	i:0 1 2 3 4 5 6 7 8
// 	v:1 2 3 4 5 6 7 8 9
// 	p:0 2 4 6 8 1 3 5 7 
//n_v:1 3 5 7 9 2 4 6 8 apply permutation on p  with k=1                  
//n_v:1 5 9 4 8 3 7 2 6 apply permutation on p  with k=2
//n_p:0 4 8 3 7 2 6 1 5 apply permutation on p  with k=2 pos
