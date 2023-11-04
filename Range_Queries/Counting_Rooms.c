#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct PairIntInt{int f,s;}pii;

//int vis[1010][1010];
char map[1010][1010];
int X[]={0,0,1,-1};
int Y[]={1,-1,0,0};
int XX[]={0,0,-1,1,1,-1,-1,1};
int YY[]={1,-1,0,0,-1,1,1,-1};

typedef struct QueueNode{
    pii item;
    struct QueueNode* next;
}qNode;
bool isEmpty(qNode** queue){ return ((*queue)==NULL);}
void assignValue(qNode** queue,pii itm){
    (*queue)=(qNode*)malloc(sizeof(qNode));
    (*queue)->next=(*queue);
    (*queue)->item=itm;
    return; //break,continue;
}
 
void push(qNode** queue,pii itm){
    if(isEmpty(queue)){ // empty
        assignValue(queue,itm);
    }
    else{
        qNode* newnode=NULL;
        assignValue(&newnode,itm);
        (newnode)->next=(*queue)->next;
        (*queue)->next=(newnode);
        (*queue)=newnode;
    }
}
 
void pop(qNode** queue){
     if(!isEmpty(queue)){
        if((*queue)==(*queue)->next){
            (*queue)=NULL;
        }
        else{
            qNode* deleteNode=(*queue)->next;
            (*queue)->next=(deleteNode)->next;
            (deleteNode)->next=NULL;
            free(deleteNode);
        }   
     } 
     return;   
}
 
qNode* front(qNode** queue){ return (*queue)->next;}



bool isValid(int x1,int y1,int n,int m){
    if((x1<0)||(y1<0)||(x1>=n)||(y1>=m)){
        return false;
    }
    if(map[x1][y1]=='#') return false;
    return true;

}

void dfs(int n,int m,int i,int j){
    //vis[i][j]=1;
    map[i][j]='#';
    for(int dir=0;dir<4;dir++){
        int x1=i+X[dir];
        int y1=j+Y[dir];
        if(isValid(x1,y1,n,m)){
                  dfs(n,m,x1,y1);  
        }
    }
    return;
}

void bfs(int n,int m,int i,int j){
    qNode* queue=NULL;
    pii itm={.f=i,.s=j};
    push(&queue,itm);
    while(!isEmpty(&queue)){
        qNode* top=front(&queue);
        int x=top->item.f;
        int y=top->item.s;
        map[x][y]='#';
        for(int dir=0;dir<4;dir++){
            int x1=x+X[dir];
            int y1=y+Y[dir];
            if(isValid(x1,y1,n,m)){
                itm.f=x1;itm.s=y1;
                push(&queue,itm);
            }
        }
        pop(&queue); 
    }
}

int main() {
    int n,m,i,j;
    assert(fscanf(stdin,"%d %d",&n,&m)>0);
    for(i=0;i<n;i++){
        assert(fscanf(stdin,"%s",&map[i])>0);
    }
    int count=0;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(map[i][j]=='.'){
                bfs(n,m,i,j); // bfs/dfs approach
                count+=1;
            }
        }
    }
    printf("%d\n",count);
}
