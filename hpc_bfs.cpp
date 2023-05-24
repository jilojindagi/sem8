#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

const int MAX = 100000;
std::vector<int> graph[MAX];
bool visited[MAX];

void bfs(int node) {
    std::queue<int> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        std::cout << curr << " ";

        // Iterate over the neighbors of the current node in parallel
        #pragma omp parallel for
        for (int i = 0; i < graph[curr].size(); i++) {
            int adj = graph[curr][i];
            if (!visited[adj]) {
                // Use a critical section to ensure thread safety when updating shared variables
                #pragma omp critical
                {
                    visited[adj] = true;
                    q.push(adj);
                }
            }
        }
    }
}

int main() {
    int n, m, start;
    std::cout << "Enter the number of nodes, edges, and start node: ";
    std::cin >> n >> m >> start;
    std::cout << "Enter the edges: " << std::endl;

    // Read the graph edges and build the adjacency list representation
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Initialize the visited array in parallel
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    std::cout << "Breadth First Search (BFS) traversal: ";
    bfs(start);
    std::cout << std::endl;

    return 0;
}
