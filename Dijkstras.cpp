#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<queue>
using namespace std;

class graph{
  public:
    map<int, vector<pair<int,int> > > adj;

    void addVertex(int v){
        auto it = adj.find(v);
        if(it != adj.end()) return;
        else{
            vector<pair<int,int> > temp;
            adj[v] = temp;
        }
    }

    // Edge directed from u to v. v is neighbour of u only
    void addEdge(int u,int v,int l){
        vector<pair<int,int> > temp1;
        vector<pair<int,int> > temp2;
        auto it = adj.find(u);
        if(it == adj.end()){
            adj[u] = temp1;
        }
        it = adj.find(v);
        if(it == adj.end()){
            adj[v] = temp2;
        }
        adj[u].push_back(make_pair(v,l));
        return;
    }

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

class Node {
public:
    int vertex;
    int label;

    Node(int v, int d) {
        vertex = v;
        label = d;
    }

    ~Node() {
    }
};

// Comparator for the priority queue
struct CompareNode {
    bool operator()(Node* const & n1, Node* const & n2) {
        // Return true if n1 should come after n2 in the priority queue
        return n1->label > n2->label;
    }
};

vector<int> shortestPath(graph g,int start){
    map<int,vector<pair<int,int> > > adj = g.adj;
    int n = adj.size();

    // Min heap of Scomp
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> pq;
    
    // Track of set S
    vector<bool> S(n);
    for(int i=0; i<n; i++){
        S[i] = 0;
    }
    // Array of shortest distance
    vector<int> d(n);
    for(int i=0; i<n; i++){
        d[i] = INT16_MAX;
    }

    Node* reference[n];

    for(auto it=adj.begin(); it!=adj.end(); ++it){
        int v = it->first;
        Node* temp = new Node(v,d[v]);
        reference[v] = temp;
    }

    d[start] = 0;
    reference[start]->label = 0;
    for(int i=0; i<n; i++){
        pq.push(reference[i]);
    }

    while(!pq.empty()){
        int v = pq.top()->vertex;
        pq.pop();
        S[v] = 1;

        for(int i=0; i<adj[v].size(); i++){
            int w = adj[v][i].first;
            if(S[w] == 0){
                d[w] = min(d[w],d[v]+adj[v][i].second);
                reference[w]->label = d[w];
                
                priority_queue<Node*, std::vector<Node*>, CompareNode> new_pq;
                while(!pq.empty()){
                    new_pq.push(pq.top());
                    pq.pop();
                }
                pq = new_pq;
            }
        }
    }

    return d;
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
    g.printAdjList();

    // Shortest path
    vector<int> d = shortestPath(g,0);
    for(int i=0; i<d.size(); i++){
        cout<<0<<" -> "<<i<<": "<<d[i]<<endl;
    }
}