#include <bits/stdc++.h>

const int N = 200010;
const int S = 1 << 18;

int n, q, a[N];
//using namespace std;
// struct node {
//     long long sum, pref;
//     node(long long sum, long long pref) : sum(sum), pref(pref) {}
//     node(long long x = 0) : sum(x), pref(max(0LL, x)) {}
//     friend node operator+(const node &a, const node &b) {
//         return {a.sum + b.sum, max(a.pref, a.sum + b.pref)};
//     }
// } tt[S << 1];

typedef struct{
    long long sum,pref;
}node;

node tt[S<<1];

long long max(long long a,long long b){
    if(a>=b) return a;
    else return b;
}

node Node(long long val){
    return {.sum=(val),.pref=max(0LL,val)};
}

node add(node fr,node sc){
    node third = {.sum=(fr.sum+sc.sum),.pref=max((fr.pref),(fr.sum+sc.pref))};
    return third;
}

void build(int k=1,int l=1,int r=n){
    if(l==r){
        tt[k] = Node(a[l]);
        return;
    }
    int mid = (l+r)/2;
    
    build((2*k),l,mid);
    build((2*k)|1,mid+1,r);
    tt[k] = add(tt[(2*k)],tt[(2*k)|1]);
}

void update(int index,int val,int k=1,int l=1,int r=n){
    if(l==r){
        tt[k] = Node(val); return;
    }
    int mid = (l+r)/2;
    if(index<=mid) update(index,val,(2*k),l,mid);
    else update(index,val,(2*k)|1,mid+1,r);
    tt[k] = add(tt[(2*k)],tt[(2*k)|1]);
}

node query(int qs,int qe,int s=1,int e=n,int k=1){
    if((qs>e)||(qe<s)) return {0,0};
    if((qs<=s)&&(qe>=e)) return tt[k];
    int m = (s+e)/2;
    node p1 = query(qs,qe,s,m,(2*k));
    node p2 = query(qs,qe,m+1,e,(2*k)|1);
    return add(p1, p2);
}
void solve(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);    
    }
    //printf("%d\n",n);
     build();
    // for(int i=0;i<(2*n);i++){
    //   // printf("%lli,",tt[i]);
    // }
    //printf("\n");
    for(int i=0;i<q;i++){ int ch,s,e;
        scanf("%d%d%d",&ch,&s,&e);
        if(ch==1){ update(s,a[s]=e);}
        else printf("%lli\n",query(s,e).pref);
    }
}
int main(){
    solve();
}
