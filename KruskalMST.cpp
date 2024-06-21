#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<queue>
#include<algorithm>
using namespace std;

class UnionFind{
  public:
    int vertex;
    UnionFind* parent;
    int rank;  // No of nodes in a set

    UnionFind(int u){
        vertex = u;
        parent = NULL;
        rank = 1;
    }

    ~UnionFind(){
    }
};

UnionFind* find(UnionFind* x){
    UnionFind* temp1 = x;
    UnionFind* temp2 = x->parent;
    while(temp2 != NULL){
        temp1 = temp1->parent;
        temp2 = temp2->parent;
    }

    // Path compression
    if(x->parent == NULL) return x;
    else if(x->parent != temp1){
        x->parent = temp1;
    }
    return temp1;
}

void Union(UnionFind* x,UnionFind* y){
    if(x->rank == y->rank){
        y->parent = x;
        x->rank += y->rank;
    }
    else if(x->rank < y->rank){
        x->parent = y;
        y->rank += x->rank;
    }
    else{
        y->parent = x;
        x->rank += y->rank;
    }
}

class graph{
  public:
    map<int, vector<pair<int,int> > > adj;  // u to v is edge of length l where pair<v,l>

    void addVertex(int v){
        auto it = adj.find(v);
        if(it != adj.end()) return;
        else{
            vector<pair<int,int> > temp;
            adj[v] = temp;
        }
    }

    void addEdge(int u,int v,int l){
        auto it = adj.find(u);
        if(it == adj.end()){
            addVertex(u);
        }
        it = adj.find(v);
        if(it == adj.end()){
            addVertex(v);
        }
        adj[u].push_back(make_pair(v,l));
        adj[v].push_back(make_pair(u,l));
    }

    // u -> v(l) means there is edge from u to v of length l
    void printAdjList(){
        for(auto it=adj.begin(); it!=adj.end(); ++it){
            cout<<it->first<<" -> ";
            if(it->second.size() != 0){
                for(int i=0; i<it->second.size(); i++){
                    cout<<it->second[i].first<<"("<<it->second[i].second<<")"<<" ";
                }
            }
            cout<<endl;
        }
    }
};

// Kruskal's algorithm (greedy)
    // comparator function
bool sortByLength(const pair<pair<int,int>,int> &a,const pair<pair<int,int>,int> &b){
    return a.second < b.second;
}

graph MST(graph g){
    map<int,vector<pair<int,int> > > adj1 = g.adj;
    int n = adj1.size();

    // creating data structure to store edge with length
    vector<pair<pair<int,int>,int> > edge_length;
    for(auto it=adj1.begin(); it!=adj1.end(); ++it){
        int u = it->first;
        vector<pair<int,int> > neigh = it->second;
        int Nneigh = neigh.size();

        for(int i=0; i<Nneigh; i++){
            int v = neigh[i].first;
            int length = neigh[i].second;

            // Avoid duplicate edges
            if (u < v) { 
                edge_length.push_back(make_pair(make_pair(u, v), length));
            }
        }
    }

    // Sorting edge_length vector
    sort(edge_length.begin(),edge_length.end(),sortByLength);

    // Creating spanning tree
    graph G;
    
    // Construction map to develope correspondence for int and nodes
    vector<UnionFind*> nodes(n);
    for(auto it=adj1.begin(); it!=adj1.end(); ++it){
        int vertex = it->first;
        UnionFind* node = new UnionFind(vertex);
        nodes[vertex] = node;
    }

    // Adding first edge
    G.addEdge(edge_length[0].first.first,edge_length[0].first.second,edge_length[0].second);
    Union(nodes[edge_length[0].first.first],nodes[edge_length[0].first.second]);

    int m = 1;  // Record of #edges of G
    int p = 1;  // iterator for vector edge_length
    while(m < n-1){
        int u = edge_length[p].first.first;
        int v = edge_length[p].first.second;
        int l = edge_length[p].second;

        UnionFind* rootU = find(nodes[u]);
        UnionFind* rootV = find(nodes[v]);

        if(rootU != rootV){
            G.addEdge(u,v,l);
            Union(rootU,rootV);
            m++;
        }
        p++;
    }
    
    // Result
    return G;
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
        int u,v,l;
        cin>>u>>v>>l;
        g.addEdge(u,v,l);
    }

    // print graph
    cout<<"Adjacency list"<<endl;
    g.printAdjList();

    // MST
    cout<<"Minimum spanning tree"<<endl;
    graph G = MST(g);
    G.printAdjList();
}