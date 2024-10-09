#include <bits/stdc++.h>
using namespace std;
#define N ((int)1e5+5)
#define mod ((int)1e9+7)
#define Black 1
#define White 0
bool visited[N];
vector<vector<int>> adj;
int dp[N][2]; // for black its 1 and white its 0

typedef long long int ll;

int modadd(int a,int b){
	a += b;
	if(a>=mod) a -= mod;
	if(a<0) a += mod;
	return a;
}

int modmul(int a,int b){
	return (ll)a*b%mod;
}

void dfs(int root){
	visited[root] = true;
	for(auto itr: adj[root]){
		if(!visited[itr]){
			dfs(itr);
			dp[root][White] =  modmul(dp[root][White],modadd(dp[itr][White],dp[itr][Black]));
			dp[root][Black] =  modmul(dp[root][Black],dp[itr][White]);
		}
		
	}
}

void solve(){
	memset(visited,false,sizeof(visited));
	memset(dp,0,sizeof(dp));
	int n,u,v,i;
	assert(fscanf(stdin,"%d",&n)>0);
	for(i=0;i<n;i++){
		vector<int> vec;
		adj.push_back(vec);
		vec.clear();
	}
	u=0,v=0;
		dp[u][0] = 1;
		dp[v][0] = 1; 
		dp[u][1] = 1;
		dp[v][1] = 1;
	for(i=0;i<(n-1);i++){
		assert(fscanf(stdin,"%d%d",&u,&v)>0);
		u--,v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
		dp[u][0] = 1;
		dp[v][0] = 1; 
		dp[u][1] = 1;
		dp[v][1] = 1;
	}
	dfs(0); // // fix 0 as root 
	printf("%d",modadd(dp[0][White],dp[0][Black]));
	return;
}

int main(/*int argc,char* argv[]*/){
	int tt=1; // assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
