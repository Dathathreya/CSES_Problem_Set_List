#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
// Coordination Compression
// Sorting 
// Fenwick Frequency Indexed tree
#define M (int)3e5+7
// https://codeforces.com/blog/entry/55274
typedef long long int ll_t;
typedef int (*compare_self_t)(const void* a, int f1, int f2);
typedef void (*swap_self_t)(const void* a, int f1, int f2);


int n, q, i = 0, seen[M], unique = 0, values[M], queries[M][3], diff = 0, coord_comp[M], qry_ans[M], ft[M];

void io_init() {
#ifdef  LocalStreet
	assert(freopen("in.txt", "r", stdin) > 0);
	assert(freopen("a_out.txt", "w", stdout) > 0);
#endif //  LocalStreet
}

int BIT_query(int idx) {
	int sum = 0;
	while (idx > 0) {
		sum += ft[idx];
		idx -= ((idx) & (-idx));
	}
	return sum;
}

void BIT_update(int idx, int val) {
	while (idx <= n) {
		ft[idx] += val;
		idx += ((idx) & (-idx));
	}
	return;
}

int compare_L(const void* a, int f1, int f2) {
	int* q1 = (int*)a;
	return (q1[3 * f1] < q1[3 * f2]);
}

int compare_M(const void* a, int f1, int f2) {
	int* q1 = (int*)a;
	return (q1[3 * f1 + 1] < q1[3 * f2 + 1]);
}

int compare_R(const void* a, int f1, int f2) {
	int* q1 = (int*)a;
	return (q1[3 * f1 + 2] < q1[3 * f2 + 2]);
}

void swap_s(const void* a, int f1, int f2) {
	int* q1 = (int*)a;
	int fr1 = q1[3 * f1], fr2 = q1[3 * f1 + 1], fr3 = q1[3 * f1 + 2];
	q1[3 * f1] = q1[3 * f2], q1[3 * f1 + 1] = q1[3 * f2 + 1], q1[3 * f1 + 2] = q1[3 * f2 + 2];
	q1[3 * f2] = fr1, q1[3 * f2 + 1] = fr2, q1[3 * f2 + 2] = fr3;
	return;
}

void heapify(const void* arr, int root, int high, compare_self_t compfn, swap_self_t swapfn) {
	int greatest = root, leftChild = 2 * root + 1, rightChild = 2 * root + 2;
	if (leftChild < high && compfn(arr, greatest, leftChild)) {
		greatest = leftChild;
	}
	if (rightChild < high && compfn(arr, greatest, rightChild)) {
		greatest = rightChild;
	}
	if (greatest != root) {
		swapfn(arr, greatest, root);
		heapify(arr, greatest, high, compfn, swapfn);
	}

}

void heapSort(const void* arr, int low, int high, compare_self_t compfn, swap_self_t swapfn) {
	for (int root = (low + (high - low) / 2); root >= 0; root--) {
		heapify(arr, root, high + 1, compfn, swapfn);
	}
	for (int len = high; len >= 0; len--) {
		swapfn(arr, 0, len);
		heapify(arr, 0, len, compfn, swapfn);
	}
	return;
}

void solve() {
	assert(scanf("%d%d", &n, &q) > 0);
	for (i = 0; i < n; i++) {
		assert(scanf("%d", &values[i]) > 0);
		queries[i][0] = values[i];
		queries[i][2] = i;
	}
	heapSort(queries, 0, n - 1, compare_L, swap_s);
	int prev = queries[0][0];
	diff = 0, unique = 1;
	for (i = 0; i < n; i++) {
		if (prev != queries[i][0]) {
			diff = diff + 1;
		}
		queries[i][1] = diff;
		prev = queries[i][0];
	}
	heapSort(queries, 0, n - 1, compare_R, swap_s); unique = 1;
	memset(coord_comp, -1, sizeof(coord_comp));
	for (i = 0; i < n; i++) {
		if (coord_comp[queries[i][1]] == -1) { // not found
			coord_comp[queries[i][1]] = unique++;
		}
		values[i] = coord_comp[queries[i][1]];
	}

	memset(ft, 0, sizeof(ft));
	memset(queries, 0, sizeof(queries));
	for (i = 0; i < q; i++) {
		assert(scanf("%d%d", &queries[i][0], &queries[i][1]) > 0); // L,R
		queries[i][2] = i + 1;
	}

	// use co-ordinate compression to use array as hash-maps for lookup and updating frequency 
	// we consider each new instance of visit as unique if we didnt come across already seen numbr
	// during this iteration we keep marking new number to check if it occurs in future
	// if it does occur again in future visit then we consider the past freq or count  for that same number	 
	// we remove it by updating index tree with -1 during query in offline mode
	// 1 2 3 4 1 2 3 4

	// 0 1 2 3 4
	// 3 2 3 1 2
	// 1 2 2 3 3
	// 0 1 1 2 2
	// 0 1 2 3 4
	// 3 2 3 1 2
	// 2 1 2 0 1  
	// 1 2 1 3 2   
	// 2 1 2 0 1


	heapSort(queries, 0, q - 1, compare_M, swap_s);
	ft[0] = 0;
	int  qz = 0;
	memset(seen, -1, sizeof(seen));
	for (i = 0; i < n; i++) {
		if (seen[values[i]] != -1) {
			BIT_update(seen[values[i]] + 1, -1); // discard existing counting if already seen freq 
		}
		seen[values[i]] = i;
		BIT_update(i + 1, 1);

		while ((qz < q) && (queries[qz][1] == i + 1)) { // Current is ending
			int left = queries[qz][0], right = queries[qz][1], index = queries[qz][2];
			qz++;
			qry_ans[index - 1] = BIT_query(right) - BIT_query(left - 1);
		}

	}
	for (i = 0; i < q; i++) {
		printf("%d\n", qry_ans[i]);
	}
	return;
}

int main() {
	io_init();
	int tt = 1;
	// assert(scanf("%d", &tt) > 0);
	while (tt--) {
		solve();
	}
}
