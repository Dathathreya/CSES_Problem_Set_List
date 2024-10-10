#include <stdio.h>
#include <string.h>
#include <assert.h>

#define N ((int)2e5+1)
const int mod = ((int)1e9+7);
typedef long long unsigned  llu;
typedef long long int ll;

int mat[51][51],identity[51][51],temp[51][51];

int modadd(int a,int b){
	a += b;
	if(a>=mod) a-=mod;
	return a;
}

int modmul(int a,int b){
	a = (ll)a*b%mod;
	if(a<0) a+=mod;
	return a;
}

void mat_mul_ints(const void* mat1,const void* mat2,const void* temp1,int n,int offset){
	int i,j,k;
	// m1 - fixRow,varyColumn m2 - varyRowFixColumn
	int* m1 = (int*)mat1;
	int* m2 = (int*)mat2;
	int* temp = (int*)temp1;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++) 
		{
			for(k=0;k<n;k++)		
				temp[i*offset+j] = modadd(temp[i*offset+j] , modmul(m1[i*offset+k],m2[k*offset+j]) );
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++) 
		{
			m1[i*offset+j] = temp[i*offset+j];
			temp[i*offset+j] = 0;
		}
	}
	return;
}

void mat_expo(const void* mat,const void* identity,const void* temp,llu exponent,int n,int offset){
	while(exponent>0){
		if(exponent&1){
			mat_mul_ints(identity,mat,temp,n,offset); // applying to result identity matrix
		}
		mat_mul_ints(mat,mat,temp,n,offset); // binary exponentiation 
		exponent >>= 1;
	}
	return;
}

void solve(){
	int n,i,j,offset=51;
	llu k;
	assert(fscanf(stdin,"%d%llu",&n,&k)>0);
	memset(mat,0,sizeof(mat));
	memset(identity,0,sizeof(identity));
	memset(temp,0,sizeof(temp));
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		{
			if(i==j) identity[i][j] = 1;
			assert(fscanf(stdin,"%d",&mat[i][j])>0);
		}
	}
	mat_expo(mat,identity,temp,k,n,offset);
	int ans = 0;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		{
			ans = modadd(ans,identity[i][j]);
		}
	}
	printf("%d\n",ans);
	return;
}

int main(){
	int tt=1;
	// assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
	return 0;
}

// https://codeforces.com/problemset/problem/1105/C
