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

void dfs(int v,int a[],int d[],map<int,vector<int> > adj,int &time){
    a[v] = time++;
    auto it = adj.find(v);
    vector<int> neigh = it->second;
    for(int i=0; i<neigh.size(); i++){
        int w = neigh[i];
        if(a[w] == -1) dfs(w,a,d,adj,time);
    }
    d[v] = time++;
}

vector<pair<int,int> > DFS(graph g){
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
    int s = 0;
    while(s<n){
        if(arrival[s] == -1){
            dfs(s,arrival,departure,adj,time);
        }
        s++;
    }

    // result
    vector<pair<int,int> > ans;
    for(int i=0; i<n; i++){
        ans.push_back(make_pair(arrival[i],departure[i]));
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

    // DFS
    vector<pair<int,int> > dfs = DFS(g);
    for(int i=0; i<dfs.size(); i++){
        cout<<i<<" -> "<<dfs[i].first<<" "<<dfs[i].second<<endl;
    }
}