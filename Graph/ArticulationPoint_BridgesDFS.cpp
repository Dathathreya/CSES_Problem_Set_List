// mistakes number of vertices 
//  instead of marking visiting of neighbour did visiting of root/parent node 
// equality must be greater than or equal to when checking lowest reachable node from child node to parent node 

private: int timer=1;
  public:
    int time[200005],low[200005];
    int visited[200005],ap[200005];
    void dfsAP(vector<int> adj [],int s,int p){//,vector<int>& ap,vector<int>& visited,int low[],int time[]
        low[s] = time[s] = timer;
        timer++;
        visited[s] = 1;
        int child = 0;
        for(auto neighbour: adj[s]){
            if(neighbour==p){
                continue;
            }
            if(visited[neighbour]==0){// neigbhour must be unvisited
                dfsAP(adj,neighbour,s);
                low[s] = min(low[s],low[neighbour]);
                if((low[neighbour]>=time[s])&&(p!=-1)){
                    // neighbour node can never be reached if we remove current s node
                    ap[s] = 1;// so this has to be a AP    
                }
                child++;
            }
            else{
                low[s] = min(low[s],time[neighbour]);// neighbour node is already visited, its discov time
                // is not letting us mark current node as ap
            }
        }
        if((child>1)&&(p==-1)){
            ap[s] = 1;
        }
    }
    vector<int> articulationPoints(int V, vector<int>adj[]) {
        timer=0;
        memset(visited,0,sizeof(visited));memset(time,-1,sizeof(time));
        memset(low,-1,sizeof(low));memset(ap,0,sizeof(ap));
        timer = 1;
        for(int i=0;i<V;i++){
            if(!visited[i])// do dfs only for non-visited node
                {dfsAP(adj,i,-1);} 
        }
        vector<int> ans;
        for(int i=0;i<V;i++){
            if(ap[i])// do dfs only for non-visited node
                ans.push_back(i);
        }
        if(ans.size()==0){
            ans.push_back(-1);
        }
        return ans;
    }
