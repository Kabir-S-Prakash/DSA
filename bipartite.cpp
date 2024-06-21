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

map<int,int> BFSlevels(graph G){
    map<int,vector<int> > adj = G.adj;
    map<int,int> ans;      // BFS travel
    queue<pair<int,int> > bfsContainer;         // queue

    // Keep record of vertices traversed
    map<int, bool> covered;

    // Adding first vertex in queue
    
    bfsContainer.push(make_pair(adj.begin()->first,0));   // starting level 0
    covered[bfsContainer.front().first] = false;


    while(bfsContainer.size() != 0){
        int front = bfsContainer.front().first;
        int level = bfsContainer.front().second;

        if(covered[front]){
            bfsContainer.pop();
            continue;
        }

        //

        // change this to do whatever you want during traversal
        ans[front] = level;

        //

        for(int i=0; i<adj[front].size(); i++){
            int neigh = adj[front][i];
            if(covered.find(neigh) == covered.end()){
                covered[neigh] = false;
                bfsContainer.push(make_pair(neigh,level+1));
            }
            else{
                if(!covered[neigh]) bfsContainer.push(make_pair(neigh,level+1));
            }
        }
        covered[front] = true;
        bfsContainer.pop();
    }
    return ans;
}

bool isBipartite(graph g){
    map<int,vector<int> > adj = g.adj;
    map<int,int> levels = BFSlevels(g);
    for(auto it=adj.begin(); it!=adj.end(); ++it){
        int vertex = it->first;
        vector<int> neighbours = it->second;
        for(int i=0; i<neighbours.size(); i++){
            if(levels[vertex] == levels[neighbours[i]]) return false;
        }
    }
    return true;
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

    // isBipartite
    cout<<isBipartite(g)<<endl;
}