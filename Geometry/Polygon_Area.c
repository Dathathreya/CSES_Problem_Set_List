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

typedef struct Point{
	ll x,y;
}Point;

ll Abs(ll ans){
	return (ans<0)?(-ans):(ans);
}

Point polygon[N];

void read_point(Point* p1){
	assert(fscanf(stdin,"%lli%lli",&(p1->x),&(p1->y))>0);	
}

void solve(){
	int n,i;
	assert(fscanf(stdin,"%d",&n)>0);
	FOR(i,0,n){
		read_point(&polygon[i]);
	}
	ll ans = 0;
	FOR(i,0,n){
		ans += (polygon[i].x*polygon[(i==n-1)?(0):(i+1)].y)-(polygon[i].y*polygon[(i==n-1)?(0):(i+1)].x);
	}
	printf("%lli\n",Abs(ans));
}

int main(void){
	int tt=1;
	// assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
	return 0-0;
}
