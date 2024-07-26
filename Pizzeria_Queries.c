#include <stdio.h>
#include <assert.h>
#include <string.h>
 
#define N (1<<19)+1
#define IMN 0x80000000
#define IMX 0x7fffffff
int min(int a,int b){return ((a>=b)?(b):(a));} 

int sz = 0;

typedef struct pii{
    int f,s;
}pii;

pii sgtree[N];

void init(){
    for(int i=0;i<(N);i++){
        sgtree[i].f = sgtree[i].s = IMX; 
    }
    return ;
} 

void update(int idx,int x,int isLow){ // for inserting (Pa-a) in all values of a <=b use isLow  
    int Sz = (1<<sz);
    idx += (Sz-1);
    if(isLow) sgtree[idx].f = x;
    else  sgtree[idx].s = x;

    idx /= 2;
    while(idx>=1){
        int leftChild = 2*idx,rightChild = 2*idx + 1;
        if(isLow) sgtree[idx].f = min(sgtree[leftChild].f,sgtree[rightChild].f);
        else sgtree[idx].s = min(sgtree[leftChild].s,sgtree[rightChild].s);
        idx /= 2;
    }
    return;
}

int query(int start,int end,int isLow){ // endingIndex (1...R)
    start += ((1<<sz)-1);
    end += ((1<<sz)-1);
    int ans1 = IMX,ans2=IMX;    
    //printf("%d %d\n",start,end);
           //          1
           //     2         3
           //  4    5    6     7
           // 8 9 10 11 12 13 14 15  
    while(start<=end){
        
        if(start%2==1){
            ans1 = min(sgtree[start].f ,ans1);
            ans2 = min(sgtree[start].s,ans2);
            start++;
        }   
        if(end%2==0){
            ans1 = min(sgtree[end].f ,ans1);
            ans2 = min(sgtree[end].s,ans2);
            end--;
        }
        end /= 2,start /= 2;
    }
    if(isLow){
        return ans1;
    }
    else{
        return ans2;
    }
}

void solve(){
    int n,q,i,x,op,idx;
    sz = 0;
    assert(fscanf(stdin,"%d%d",&n,&q)>0);
    while((1<<sz)<n){
        sz++;
    }
    init(); /*setup all values in my segment tree with maximum value*/
    for(i=0;i<n;i++){
       assert(fscanf(stdin,"%d",&x)>0);
       update(i+1,x-(i+1),1);
       update(i+1,x+(i+1),0);
    }
    int Sz = 2*(1<<sz)-1;
    // for(i=0;i<Sz;i++){
    //     printf("(%d,%d)",i,sgtree[i].f);
    // }
    // printf("\n");
    // 2 segment tree for storing minimums
    // 1 segment tree -> a>bidx , value_a + a - bidx 
    // 2 segment tree -> a<bidx , value_a - a + bidx  

    for(i=0;i<q;i++){
        assert(fscanf(stdin,"%d%d",&op,&idx)>0);
        switch(op){
            case 2:{      
                int LeftMini  = query(idx,n,0); 
                int rightMini = query(1,idx,1); 
                  LeftMini  -= idx;
                  rightMini += idx;   
                printf("%d\n",min(rightMini,LeftMini));
                //printf("%d\n",min(LeftMini,rightMini)); /*calling fetch or query method*/ 
                break;
            }
            case 1:{
                assert(fscanf(stdin,"%d",&x)>0);
                //update(idx,x); /*calling update method*/   
                update(idx,x-idx,1);
                update(idx,x+idx,0);         
                break;
            }
            default:{
                break;
            }
        }
    }
    return ; 
}
 
int main()
{
    int tt=1;
    while(tt--){
        solve();
    }
    return 0;
}

            // problem statement and reason 
            // person at build k , can order smth from building at 2 ranges 
            // from building z= 1 to k -> final_value= ( p[z] - z ) + k
            // from building z= k to sz -> final_value= ( p[z] + z ) - k
            // k is constant , so we maintain 2 separate segment tree for both 
            // maintaing and querying on 2 separate things

            // updating 
            //           1
            //      2         3
            //   4    5    6     7
            // 8 9 10 11 12 13 14 15  
            // we start at leaf nodes , 2,4,8,16.... length ranges are covered 

            // querying 
            // Different Cases of parities (4 different combinations)    
            // Left = even_parity , right = even_parity  (00)
            // Left = even_parity , right = odd_parity   (01)
            // Left = odd_parity  , right = even_parity  (11)
            // Left = odd_parity  , right = odd_parity   (11)
            
            // For example case 1: left -> even(10) , right -> even (12)

            // helps us in searching elements between range R and L 
            // if (end or right) is even it would mean that taking a set further would lead us into
            // exploring a parent node that covers a most maximum value or index leaf node more than largest number(R)
            // in my query range , so stopping the exploration by not taking a step further up to parent is crucial
            

            // if (start or left) is odd it would mean that taking a step further up would lead us into
            // exploring a parent node that covers least min value as its leaf node which is lesser than my least num(L)
            // in my query range , so stop exploration by not taking a step further upto parent node if start is already odd

            // this could save us inaccurate results          
