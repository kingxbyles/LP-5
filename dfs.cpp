#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

vector<int> graph[100];
bool visited[100];

void dfs(int start)
{
    stack<int> st;

    st.push(start);

    while (!st.empty())
    {
        int node;

        // Safely access stack
        #pragma omp critical
        {
            node = st.top();
            st.pop();
        }

        if (!visited[node])
        {
            visited[node] = true;

            cout << node << " ";

            // Parallelize neighbor traversal
            #pragma omp parallel for
            for (int i = 0; i < graph[node].size(); i++)
            {
                int neighbor = graph[node][i];

                #pragma omp critical
                {
                    if (!visited[neighbor])
                    {
                        st.push(neighbor);
                    }
                }
            }
        }
    }
}

int main()
{
    graph[0].push_back(1);
    graph[0].push_back(2);

    graph[1].push_back(3);
    graph[1].push_back(4);

    graph[2].push_back(5);

    graph[4].push_back(6);

    cout << "DFS Traversal: ";

    dfs(0);

    return 0;
}