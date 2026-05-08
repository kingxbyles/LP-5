#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

vector<int> graph[100];
bool visited[100];

void bfs(int start)
{
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        cout << node << " ";

        // Parallel processing of neighbors using OpenMP
        #pragma omp parallel for
        for (int i = 0; i < graph[node].size(); i++)
        {
            int neighbor = graph[node][i];

            // Prevent race conditions
            #pragma omp critical
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
}

int main()
{
    // Creating graph

    graph[0].push_back(1);
    graph[0].push_back(2);

    graph[1].push_back(3);
    graph[1].push_back(4);

    graph[2].push_back(5);

    graph[4].push_back(6);

    cout << "BFS Traversal: ";

    bfs(0);

    return 0;
}