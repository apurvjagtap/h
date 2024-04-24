#include <iostream>
#include <queue>
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

    // Parallelized BFS function
    void BFS(int s) {
        // Mark all the vertices as not visited
        vector<bool> visited(V, false);

        // Create a queue for BFS
        queue<int> q;

        // Mark the current node as visited and enqueue it
        visited[s] = true;
        q.push(s);

        while (!q.empty()) {
            // Dequeue a vertex from queue and print it
            int u = q.front();
            cout << u << " ";
            q.pop();

            // Parallelize the loop for visiting neighboring nodes
            #pragma omp parallel for
            for (int i = 0; i < adj[u].size(); ++i) {
                int v = adj[u][i];
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
};

int main() {
    // Create a graph given in the example
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "Breadth First Traversal (starting from vertex 2): ";
    g.BFS(2);

    return 0;
}
