//https://codeforces.com/problemset/problem/2002/C

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#define min(a,b) (a>=b)?(b):(a)

typedef long long int ll;
typedef long double ld;
#define FOR(i,a,n) for(i=a;i<n;i++)
#define N (int)3e5+4
int a[N][2];

void solve(){
	int n,xs,ys,xt,yt,i;
	assert(fscanf(stdin,"%d",&n)>0);
	FOR(i,0,n){
		assert(fscanf(stdin,"%d%d",&a[i][0],&a[i][1])>0);
	}
	assert(fscanf(stdin,"%d%d",&xs,&ys)>0);
	assert(fscanf(stdin,"%d%d",&xt,&yt)>0);
	int R=0;
	ld distance_to_travel = 1ll*(xt-xs)*(xt-xs)+1ll*(ys-yt)*(ys-yt); // minimum distance to cover
	ll mini = LLONG_MAX;
	FOR(i,0,n){
		// difference 
		ld d1 = 1ll*(xt-a[i][0])*(xt-a[i][0])+1ll*(yt-a[i][1])*(yt-a[i][1]);
		if(d1<=distance_to_travel){// target point lies inside the circle no chance of reaching
			puts("NO\n");return;
		}
	}
	puts("YES");
	putchar('\n');
}

int main(void){
	int tt;
	assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
	return 0-0;
}
