#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<queue>
using namespace std;

class graph{
  public:
    map<int, vector<int> > adj;

    void addVertex(int v){
        auto it = adj.find(v);
        if(it != adj.end()) return;
        else{
            vector<int> temp;
            adj[v] = temp;
        }
    }

    void addEdge(int u,int v){
        vector<int> temp1;
        vector<int> temp2;
        auto it = adj.find(u);
        if(it == adj.end()){
            adj[u] = temp1;
        }
        it = adj.find(v);
        if(it == adj.end()){
            adj[v] = temp2;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
        return;
    }

    void printAdjList(){
        for(auto it=adj.begin(); it!=adj.end(); ++it){
            cout<<it->first<<" -> ";
            if(it->second.size() != 0){
                for(int i=0; i<it->second.size(); i++){
                    cout<<it->second[i]<<" ";
                }
            }
            cout<<endl;
        }
    }
};

void BFS(graph &G,vector<int> &ans,int label,vector<int> &Covered,int start){
    map<int,vector<int> > adj = G.adj;
    // vector<int> ans;      // BFS travel
    queue<int> bfsContainer;         // queue

    // Keep record of vertices traversed
    map<int, bool> covered;

    // Adding first vertex in queue
    bfsContainer.push(start);
    covered[bfsContainer.front()] = false;


    while(bfsContainer.size() != 0){
        int front = bfsContainer.front();
        if(covered[front]){
            bfsContainer.pop();
            continue;
        }

        // change this to do whatever you want during traversal

        ans[front] = label;
        Covered.push_back(front);
        
        //

        for(int i=0; i<adj[front].size(); i++){
            int neigh = adj[front][i];
            if(covered.find(neigh) == covered.end()){
                covered[neigh] = false;
                bfsContainer.push(neigh);
            }
            else{
                if(!covered[neigh]) bfsContainer.push(neigh);
            }
        }
        covered[front] = true;
        bfsContainer.pop();
    }
    return;
}

vector<int> labelComp(graph g){
    int n = g.adj.size();    // No of vertices
    vector<int> ans(n+1);
    for(int i=0; i<n+1; i++) ans[i] = 0;

    vector<int> covered;     // Keep record of covered vertices
    int s=1;                 // Index to find entry point of a component
    int label=1;
    while(covered.size() != n){
        while(ans[s] != 0) s++;
        BFS(g,ans,label,covered,s);
        s++;
        label++;
    }
    return ans;
}

int main(){
    int n;
    cout<<"Enter no of vertices : ";
    cin>>n;
    int m;
    cout<<"Enter no of edges : ";
    cin>>m;

    // Graph construction
    graph g;
    cout<<"Enter vertices : ";
    for(int i=0; i<n; i++){
        int u;
        cin>>u;
        g.addVertex(u);
    }
    if(m != 0) cout<<"Enter edges : ";
    for(int i=0; i<m; i++){
        int u,v;
        cin>>u>>v;
        g.addEdge(u,v);
    }

    // print graph
    g.printAdjList();

    // Labeling and remember label vector index 0 is trash don't print
    vector<int> Labels = labelComp(g);
    for(int i=1; i<Labels.size(); i++){
        cout<<i<<" : "<<Labels[i]<<endl;
    }
}