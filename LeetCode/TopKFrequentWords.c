/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef char* str_t;
int min(int f,int s){ return (f>=s)?(s):(f);}
typedef struct pair{str_t str; int count;}psi;

typedef void (*swap_func_t)(const void* arr,int f,int s);
typedef int (*comp_func_t)(const void* arr,int f,int s);

#define swapGeneric(type,a,b)\
    type c = a;\
    a=b,b=c;


int lexicographic_sort(const char* a, const char* b) {
   int lenA=strlen(a),lenB =strlen(b);
   int len = min(lenA,lenB);
   int cmp = strncmp(b,a,len); // b is compared with a 
   return (!cmp)?(lenB>lenA):(cmp>0); // if match compare len or return order
}


void pswapfn(const void* arr,int first,int second) {
    psi* temp = (psi*)arr;swapGeneric(psi,temp[first],temp[second]);
    return;}

int pcompfn(const void* arr,int first,int second){
     psi* temp = (psi*)arr;
     if(temp[first].count==temp[second].count){
         return lexicographic_sort(temp[second].str,temp[first].str);      
     }
     return temp[second].count > temp[first].count;
}

void swapfn(const void* arr,int first,int second) {
    char** temp = (char**)arr;swapGeneric(str_t,temp[first],temp[second]);
    return;}

int compfn(const void* arr,int first,int second){
    char** temp=(char**)arr;
     return lexicographic_sort(temp[first],temp[second]);      
}

void heapify(const void* words,int root,int n,comp_func_t cfn,swap_func_t sfn){
    int greatest=root,left=(2*root)+1,right=(2*root)+2;
    if((left<n)&&(cfn(words,greatest,left))){
        greatest = left;
    }
    if((right<n)&&(cfn(words,greatest,right))){
        greatest = right;
    }
    if(greatest!=root){
        sfn(words,root,greatest); // fix value at root to be greatest 
        heapify(words,greatest,n,cfn,sfn);   // fix value at left or right child 
    }
}
void heapSort(const void* words,int wordsSize,comp_func_t cfn,swap_func_t sfn)
{
    int root,n=wordsSize;
    for(root=(n/2)-1;root>=0;root--){
        heapify(words,root,n,cfn,sfn);
    }  
    for(int len=n-1;len>=1;len--){
        sfn(words,0,len);   // fixed last item as greatest
        heapify(words,0,len,cfn,sfn);  // fix heap for length i-1 excluding current last at each iteration 
    }
}

char** topKFrequent(char** words, int wordsSize, int k, int* returnSize) 
{
    // heapSort, MergeSort
    heapSort(words,wordsSize,compfn,swapfn);
    psi pairs[wordsSize];
    int z=0,y=0;
    pairs[z].str=words[0],pairs[z].count=1;
    // for(int i=0;i<wordsSize;i++){
    //     printf("%s,",words[i]);
    // }
    // printf("\n");
    for(int i=1;i<wordsSize;i++){
        if(strcmp(words[i-1],words[i])!=0){
            //printf("inside..");
            z+=1;
            pairs[z].str=words[i],pairs[z].count=1;
        }
        else
         pairs[z].count+=1;
    }
    
    heapSort(pairs,z+1,pcompfn,pswapfn);
    // for(int p=0;p<=z;p++){
    //     printf("(%s,%d),",pairs[p].str,pairs[p].count);
    // }
    // printf("\n");
    y=0;
    for(int i=z;y<(k);i--){
        words[y]=pairs[i].str;
        y++;
    }
    *returnSize=k;
    
    return words;
}
