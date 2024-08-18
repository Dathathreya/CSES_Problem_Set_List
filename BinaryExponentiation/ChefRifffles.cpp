#include <bits/stdc++.h>
using namespace std;

vector<int> applyPermutation(vector<int> seq,vector<int> perm){
        vector<int> newSeq(seq.size());
        for(int i=0;i<seq.size();i++){
            newSeq[i] = (seq[perm[i]]);    
        }
        return newSeq;
}

vector<int> permute(vector<int> sequence,vector<int> permutation,int rep){
    while(rep){
        if(rep&1){
            sequence = applyPermutation(sequence,permutation);        
        }
        permutation = applyPermutation(permutation,permutation);
        rep >>= 1;
    }   
    return sequence;
}

void chef_and_riffles(int n,int repeat){
	vector<int> sequence(n,0);
	vector<int> permutation(n,0);
	iota(sequence.begin(),sequence.end(),1);
	for(int i=0;i<n;i++){
	     if(i<n/2) permutation[i]=2*i;
         else if((n%2==1)&&(n/2==i)) permutation[i]=2*i;
	    else {permutation[i]=(i-(n/2-(n%2==0))  + i-(n/2-(n%2==0)) -1);} 
	}
	sequence=permute(sequence,permutation,repeat);
	for(int i=0;i<n;i++){
		printf("%d ",sequence[i]);
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
