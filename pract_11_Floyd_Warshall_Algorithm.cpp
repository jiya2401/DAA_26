// Time Complexity: O(V^3)
// Space Complexity: O(V^2)

#include <iostream>
using namespace std;

#define V 4
#define INF 99999

void floydWarshall(int dist[V][V])
{
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] =
                        dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "\nShortest Distance Matrix:\n";

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}
    
int main()
{
    int graph[V][V] = {
        {0,   2,   INF, 3},
        {1,   0,   2,   INF},
        {INF, INF, 0,   INF},
        {4,   INF, 3,   0}
    };

    cout << "Initial Distance Matrix:\n";

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (graph[i][j] == INF)
                cout << "INF\t";
            else
                cout << graph[i][j] << "\t";
        }
        cout << endl;
    }

    floydWarshall(graph);

    return 0;
}
