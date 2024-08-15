//https://www.codechef.com/problems/PERMCYCQUERY 
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

typedef long long ll;

typedef struct Point{
	int x,y;
}Point;

int max(int a,int b){
	if(a>b) return a;
	return b;
}

int min(int a,int b){
	if(a<b) return a;
	return b;
}

bool isValidProjection(int a,int b,int c,int d){
	if(a>b){
		int t = a;a=b,b=t; // maximize b
	}
	if(c>d){
		int t = c;c=d,d=t; // minimize c
	}
	return max(a,c) <= min(b,d);
	// a b c d in order
	// a------b 
	//    c------d this is what we want
}

short orientation(Point* p1,Point* p2,Point* p3){
	ll pdt1 = (1ll*((p2->x)-(p1->x))*((p3->y)-(p1->y))) -(1ll*((p3->x)-(p1->x))*((p2->y)-(p1->y)));

	if(pdt1==0) return 0;
	return (pdt1<0)?(1):(2);
}

void read_point(Point* p1){
	assert(scanf("%d%d",&(p1->x),&(p1->y))>0);
	return;
}


void solve(){
	// Intersection of Two Line segments 
	Point p1[1],p2[1],p3[1],p4[1];
	read_point(p1);
	read_point(p2);
	read_point(p3);
	read_point(p4);

	int op1 = orientation(p1,p2,p3);
	int op2 = orientation(p1,p2,p4);
	int op3 = orientation(p3,p4,p1);
	int op4 = orientation(p3,p4,p2);

	if((op1!=op2)&&(op3!=op4)){
		puts("YES\n");return;
	}
	if((op1==0)&&(op4==0)){
		if(isValidProjection(p1->x,p2->x,p3->x,p4->x)&&isValidProjection(p1->y,p2->y,p3->y,p4->y)){
			puts("YES\n");return;
		}
	}
	puts("NO\n");
	
	//puts("YES\n");
	// check1:
	// 	 	 /(1)
	// 		/     (4)-----(3)
       //  /(2)

	// check2:	
	// 	 	 /(3)
	// 		/      (2)-----(1)
       //  /(4)
	
}

int main(){
	int tt=1;
	assert(scanf("%d",&tt)>0);
	while(tt--){
		solve();
	}
}
