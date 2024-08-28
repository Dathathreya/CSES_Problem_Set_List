#include <stdio.h>
#include <assert.h>
 
#include <string.h>
 
#define N (1<<19)+7
typedef long long unsigned ll;
//typedef long long unsigned  llu;
int values[N], stk[N], sz, n, q, i;
 
ll suffix[N], prefix[N];
 
typedef struct Segnode {
	int idx, maxi;
}snode;
 
typedef struct Istree {
	snode sgt[N];
	int log_sz;
}Istree;
 
Istree ist[1];
 
 
static void io_init() {
#ifdef  LocalStreetLampsLitOnFire
	assert(freopen("in.txt", "r", stdin) > 0);
	assert(freopen("a_out.txt", "w", stdout) > 0);
#endif //  LocalStreetLampsLitOnFire
}
 
static void build_ist(Istree* ist1, int n) {
	sz = 0;
	memset(ist1->sgt, 0, sizeof(ist1->sgt));
	ist1->log_sz = 0;
	while (1 << (ist1->log_sz) < n) {
		ist1->log_sz++;
	}
	ist1->log_sz = 1 << ist1->log_sz;
	memset(stk, 0, sizeof(stk));
	return;
}
 
void update(Istree* ist1, int idx, int val) {
	int un_manipulated = idx + 1;
	idx += (ist1->log_sz);
	ist1->sgt[idx].maxi = val;
	ist1->sgt[idx].idx = un_manipulated;
	idx /= 2;
	while (idx > 0) {
		int left = 2 * idx, right = 2 * idx + 1;
		if (ist1->sgt[idx].maxi < ist1->sgt[left].maxi) {
			ist1->sgt[idx].maxi = ist1->sgt[left].maxi;
			ist1->sgt[idx].idx = ist1->sgt[left].idx;
		}
		if (ist1->sgt[idx].maxi < ist1->sgt[right].maxi) {
			ist1->sgt[idx].maxi = ist1->sgt[right].maxi;
			ist1->sgt[idx].idx = ist1->sgt[right].idx;
		}
		idx /= 2;
	}
	return;
}
 
int query(Istree* ist1, int left, int right) {
	left += (ist1->log_sz); right += (ist1->log_sz);
	int ans_i = -1, val = 0;
	while (left <= right) {
		if (left & 1) {
			if (val < ist1->sgt[left].maxi) {
				val = ist1->sgt[left].maxi;
				ans_i = ist1->sgt[left].idx;
			}
			left++;
		}
		if (right % 2 == 0) {
			if (val < ist1->sgt[right].maxi) {
				val = ist1->sgt[right].maxi;
				ans_i = ist1->sgt[right].idx;
			}
			right--;
		}
		left /= 2; right /= 2;
	}
	return ans_i;
}
 
static void solve() {
	assert(fscanf(stdin, "%d%d", &n, &q));
	prefix[0] = 0;
	build_ist(ist, n);
	for (i = 0; i < n; i++) { // next greatest element
		assert(fscanf(stdin, "%d", &values[i]));
		prefix[i + 1] = prefix[i] + values[i];
		update(ist, i, values[i]);
	}
	for (i = n - 1; ~i; i--) { // next greatest element
		while (sz && (values[i] >= values[stk[sz - 1]])) {
			sz--;
		}
		if (!sz) {
			suffix[i] = values[i] * (n - i); // including itself till end 
		}
		else {
			suffix[i] = 1llu * values[i] * (stk[sz - 1] - i); // current num is greater till next greatest
			suffix[i] += suffix[stk[sz - 1]];
		}
		stk[sz] = i;
		sz++;
	}
	for (i = n - 1; ~i; i--) { // next greatest element
		suffix[i + 1] = suffix[i];
	}
	int L, R;
	for (i = 0; i < q; i++) {
		assert(fscanf(stdin, "%d%d", &L, &R));
		int max_index = query(ist, L - 1, R - 1);
		ll Suffixsum = 1llu * values[max_index - 1] * (R - max_index + 1);
		Suffixsum += suffix[L] - suffix[max_index];
		Suffixsum -= (prefix[R] - prefix[L - 1]);
		printf("%llu\n", Suffixsum);
	}
}
 
int main() {
	int tt = 1;
	io_init();
	// assert(fscanf(stdin,"%d",&tt));
	while (tt--) {
		solve();
	}
	return 0;
}
