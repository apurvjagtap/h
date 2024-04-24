#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    // DFS traversal function
    void DFSUtil(int v, vector<bool>& visited) {
        // Mark the current node as visited
        visited[v] = true;

        // Print the current node
        cout << v << " ";

        // Parallelize the loop for visiting neighboring nodes
        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i) {
            int u = adj[v][i];
            if (!visited[u]) {
                // Recur for each unvisited neighboring node
                DFSUtil(u, visited);
            }
        }
    }

    // DFS traversal starting from a given vertex
    void DFS(int v) {
        // Mark all vertices as not visited
        vector<bool> visited(V, false);

        // Call the recursive helper function to print DFS traversal
        DFSUtil(v, visited);
    }
};

int main() {
    // Create a graph given in the example
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    cout << "Depth First Traversal (starting from vertex 0): ";
    g.DFS(0);

    return 0;
}
