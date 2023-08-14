#include <stdio.h>


#define FOR(i,a,n) for(i=a;i<=n-1;i++)

void solve()
{
int n,q,i,j,r1,c1,r2,c2;
scanf("%d %d",&n,&q);
char s[n][n];
int dp[n+1][n+1];
char ch[n];
FOR(i,0,n)
{
	scanf("%s",&ch);
	FOR(j,0,n){
		s[i][j]=ch[j];
	}
}

FOR(i,1,(n+1))
{
FOR(j,1,(n+1))
{
 dp[i][j]= dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1]+((s[i-1][j-1]=='*')?(1):(0));
}	
}
 
FOR(i,0,q){
	int r1,c1,r2,c2;
	fscanf(stdin,"%d %d %d %d",&r1,&c1,&r2,&c2);
	printf("%d\n",dp[r2][c2]-dp[r1-1][c2]-dp[r2][c1-1]+dp[r1-1][c1-1]);
}
 
}
 
int main()
{
	int tt;
	tt=1;
	while(tt--)
	{
		solve();
	}
}