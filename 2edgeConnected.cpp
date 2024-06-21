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

int dfs(int v,int a[],int d[],map<int,vector<int> > adj,int &time,int parent){
    a[v] = time++;

    // Deepest back edge keeper
    int dbe = a[v];

    auto it = adj.find(v);
    vector<int> neigh = it->second;
    for(int i=0; i<neigh.size(); i++){
        int w = neigh[i];
        if(w == parent) continue;
        if(a[w] == -1){
            dbe = min(dbe,dfs(w,a,d,adj,time,v));
        }
        else dbe = min(dbe,a[w]);
    }
    d[v] = time++;

    // Checking no bridge condition
    if(dbe >= a[v] and v !=0) return -1;
    return dbe;
}

bool TwoEC(graph g){
    // Reading graph
    map<int,vector<int> > adj = g.adj;
    int n = adj.size();

    // Creating time keepers
    int arrival[n];
    int departure[n];
    for(int i=0; i<n; i++){
        arrival[i] = -1;
    }
    for(int i=0; i<n; i++){
        departure[i] = -1;
    }

    // DFS
    int time = 0;
    int ans = dfs(0,arrival,departure,adj,time,-1);

    // result
    if(ans == -1) return false;
    else return true;
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

    // Checking 2edge Connected
    cout<<TwoEC(g);
}