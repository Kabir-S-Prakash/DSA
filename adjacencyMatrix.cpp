#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjMatrix;
    unordered_map<int, int> vertexIndexMap; // Maps vertex value to matrix index
    int numVertices;

public:
    Graph() : numVertices(0) {}

    void addVertex(int vertex) {
        if (vertexIndexMap.find(vertex) == vertexIndexMap.end()) {
            vertexIndexMap[vertex] = numVertices;
            numVertices++;
            adjMatrix.resize(numVertices);
            for (int i = 0; i < numVertices; ++i) {
                adjMatrix[i].resize(numVertices, 0);
            }
        } else {
            cout << "Vertex " << vertex << " already exists.\n";
        }
    }

    void addEdge(int u, int v) {
        if (vertexIndexMap.find(u) == vertexIndexMap.end() || vertexIndexMap.find(v) == vertexIndexMap.end()) {
            cout << "One or both vertices not found.\n";
            return;
        }
        int uIndex = vertexIndexMap[u];
        int vIndex = vertexIndexMap[v];
        adjMatrix[uIndex][vIndex] = 1;
        adjMatrix[vIndex][uIndex] = 1; // For undirected graph
    }

    void printMatrix() {
        // Create a reverse map to print vertex values
        unordered_map<int, int> indexVertexMap;
        for (const auto& pair : vertexIndexMap) {
            indexVertexMap[pair.second] = pair.first;
        }

        // Print column headers
        cout << "  ";
        for (int i = 0; i < numVertices; ++i) {
            cout << indexVertexMap[i] << " ";
        }
        cout << endl;

        // Print rows with row headers
        for (int i = 0; i < numVertices; ++i) {
            cout << indexVertexMap[i] << " ";
            for (int j = 0; j < numVertices; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g;

    g.addVertex(2);
    g.addVertex(5);
    g.addVertex(11);
    g.addVertex(13);
    g.addVertex(19);

    g.addEdge(2, 5);
    g.addEdge(2, 11);
    g.addEdge(5, 11);
    g.addEdge(5, 13);

    cout << "Adjacency Matrix:\n";
    g.printMatrix();

    cout << "Adding a new vertex and an edge:\n";
    g.addVertex(23);
    g.addEdge(13, 19);
    g.addEdge(19, 23);

    g.printMatrix();

    return 0;
}