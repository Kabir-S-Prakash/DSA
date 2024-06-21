#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <climits>
#include <set>

using namespace std;

class graph {
public:
    map<int, vector<pair<int, int>>> adj;  // u to v is edge of length l where pair<v,l>

    void addVertex(int v) {
        auto it = adj.find(v);
        if (it != adj.end()) return;
        else {
            vector<pair<int, int>> temp;
            adj[v] = temp;
        }
    }

    void addEdge(int u, int v, int l) {
        auto it = adj.find(u);
        if (it == adj.end()) {
            addVertex(u);
        }
        it = adj.find(v);
        if (it == adj.end()) {
            addVertex(v);
        }
        adj[u].push_back(make_pair(v, l));
        adj[v].push_back(make_pair(u, l));
    }

    // u -> v(l) means there is edge from u to v of length l
    void printAdjList() {
        for (auto it = adj.begin(); it != adj.end(); ++it) {
            cout << it->first << " -> ";
            if (it->second.size() != 0) {
                for (int i = 0; i < it->second.size(); i++) {
                    cout << it->second[i].first << "(" << it->second[i].second << ") ";
                }
            }
            cout << endl;
        }
    }
};

graph MST(graph g) {
    graph mst;

    // pq<label,vertex>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    map<int, int> key;          // key[v] = label[v]
    map<int, int> parent;       // parent[v] = u means v inserted after u
    set<int> inMST;

    for (auto it = g.adj.begin(); it != g.adj.end(); ++it) {
        key[it->first] = INT_MAX;      // Initial label of each vertex infinity
        parent[it->first] = -1;        // Initial parent -1
    }

    int start = g.adj.begin()->first;
    pq.push(make_pair(0, start));
    key[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST.find(u) != inMST.end()) {
            continue;
        }

        inMST.insert(u);

        for (auto& neighbor : g.adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // If v in Scompl & length of u-v is less than current label then update it 
            if (inMST.find(v) == inMST.end() && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // Construct the MST graph
    for (auto it = parent.begin(); it != parent.end(); ++it) {
        if (it->second != -1) {
            mst.addEdge(it->second, it->first, key[it->first]);
        }
    }

    return mst;
}

int main() {
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
