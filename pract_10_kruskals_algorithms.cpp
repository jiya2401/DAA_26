// Part of code                         Complexity
// ---------------------------------------------------
// Reading E edges                      O(E)
// Initializing parent array            O(V)
// std::sort() on E edges               O(E log E)
// Processing up to E edges             O(E log V)
// ---------------------------------------------------
// Overall                              O(E log E)

// Time Complexity: O(E log E)

#include <iostream> 
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;


// Structure to store an edge
struct Edge
{
    int u; 
    int v; 
    int weight;
};


// Find the parent of a vertex
int findParent(vector<int> &parent, int x)
{
    while(parent[x] != x)
    {
        x = parent[x];
    }

    return x;
}


// Join two sets
void unionSets(vector<int> &parent,
               vector<int> &rank,
               int a,
               int b)
{
    a = findParent(parent, a);
    b = findParent(parent, b);

    if(a == b)
        return;

    if(rank[a] < rank[b])
    {
        parent[a] = b;
    }
    else if(rank[a] > rank[b])
    {
        parent[b] = a;
    }
    else
    {
        parent[b] = a;
        rank[a]++;
    }
}


int main()
{
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    if(V <= 0)
    {
        cout << "Invalid number of vertices.";
        return 0;
    }

    cout << "Enter number of edges: ";
    cin >> E;

    if(E < 0)
    {
        cout << "Invalid number of edges.";
        return 0;
    }


    vector<Edge> edges(E);

    cout << "Enter edges (u v weight):\n";

    for(int i = 0; i < E; i++)
    {
        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].weight;

        if(edges[i].u < 1 ||
           edges[i].u > V ||
           edges[i].v < 1 ||
           edges[i].v > V)
        {
            cout << "Invalid vertex number.";
            return 0;
        }

        if(edges[i].weight <= 0)
        {
            cout << "Weight must be positive.";
            return 0;
        }
    }


    // ---------------- KRUSKAL'S ALGORITHM ----------------

    vector<int> parent(V + 1);
    vector<int> rank(V + 1, 0);

    for(int i = 1; i <= V; i++)
    {
        parent[i] = i;
    }


    int operations = 0;
    int mstEdges = 0;
    int totalWeight = 0;


    auto start = high_resolution_clock::now();


    // Sort edges according to weight
    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b)
         {
             return a.weight < b.weight;
         });


    // Process edges from smallest to largest
    for(int i = 0; i < E; i++)
    {
        operations++;

        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        int parentU = findParent(parent, u);
        int parentV = findParent(parent, v);


        // If parents are different, no cycle is formed
        if(parentU != parentV)
        {
            cout << ""; // no extra output during timing

            unionSets(parent, rank,
                      parentU, parentV);

            totalWeight += weight;
            mstEdges++;

            // MST needs exactly V-1 edges
            if(mstEdges == V - 1)
                break;
        }
    }


    auto end = high_resolution_clock::now();

    auto timeTaken =
        duration_cast<nanoseconds>(end - start);


    // ---------------- CHECK MST ----------------

    if(mstEdges != V - 1)
    {
        cout << "\nGraph is disconnected.";
        return 0;
    }


    // ---------------- DISPLAY MST ----------------

    cout << "\n\n========== KRUSKAL'S MINIMUM SPANNING TREE ==========\n";

    cout << "\nTotal MST Weight : "
         << totalWeight;

    cout << "\nMST Edges        : "
         << mstEdges;

    cout << "\nOperations       : "
         << operations;

    cout << "\nExecution Time   : "
         << timeTaken.count()
         << " ns";


    cout << "\n\n========== COMPLEXITY ==========";

    cout << "\nTime Complexity  : O(E log E)";
    cout << "\nSpace Complexity : O(V + E)";

    cout << "\n=================================\n";


    return 0;
}