//  TIME & SPACE COMPLEXITY SUMMARY
//  Method    Time         Space      Notes
//  DFS       O(V + E)     O(V)       Recursive calls use stack space
//  BFS       O(V + E)     O(V)       Queue stores nodes level by level
#include <iostream>
#include <vector>
#include <queue> 
#include <chrono>

using namespace std; 
using namespace std::chrono;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v); 
        adj[v].push_back(u);  
    }

    void DFSUtil(int v, vector<bool> &visited, vector<int> &order) {
        visited[v] = true;
        order.push_back(v);

        for (int neighbor : adj[v]) {
            if (!visited[neighbor])
                DFSUtil(neighbor, visited, order);
        }
    }

    vector<int> DFS(int start) {
        vector<bool> visited(V, false);
        vector<int> order;
        DFSUtil(start, visited, order);
        return order;
    }

    vector<int> BFS(int start) {
        vector<bool> visited(V, false);
        vector<int> order;
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            order.push_back(node);

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return order;
    }
};

int main() {
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    // DFS Time Analysis
    auto startDFS = high_resolution_clock::now();
    vector<int> dfsOrder = g.DFS(start);
    auto endDFS = high_resolution_clock::now();
    auto dfsTime = duration_cast<nanoseconds>(endDFS - startDFS);

    // BFS Time Analysis
    auto startBFS = high_resolution_clock::now();
    vector<int> bfsOrder = g.BFS(start);
    auto endBFS = high_resolution_clock::now();
    auto bfsTime = duration_cast<nanoseconds>(endBFS - startBFS);

    // Print results AFTER timing
    cout << "\nDFS Traversal: ";
    for (int v : dfsOrder) cout << v << " ";

    cout << "\n\nBFS Traversal: ";
    for (int v : bfsOrder) cout << v << " ";

    cout << "\n\nExecution Time:";
    cout << "\nDFS: " << dfsTime.count() << " ns";
    cout << "\nBFS: " << bfsTime.count() << " ns";

    return 0;
}