// DFS using OpenMP

#include <iostream>
#include <stack>
#include <vector>
#include <omp.h>

const int MAX = 100000;
std::vector<int> graph[MAX]; // Adjacency list representation of the graph
bool visited[MAX]; // Array to keep track of visited nodes

void dfs(int node) {
    std::stack<int> s; // Stack to store nodes during DFS traversal
    s.push(node); // Start from the given start node

    while (!s.empty()) {
        int curr = s.top(); // Get the current node from the stack
        s.pop();

        if (!visited[curr]) { // Check if the current node is not visited
            visited[curr] = true; // Mark the current node as visited
            std::cout << curr << " "; // Print the current node

            #pragma omp parallel for
            for (int i = 0; i < graph[curr].size(); i++) {
                int adj = graph[curr][i]; // Get the adjacent node
                if (!visited[adj]) { // Check if the adjacent node is not visited
                    #pragma omp critical
                    {
                        s.push(adj); // Push the adjacent node onto the stack
                    }
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
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v); // Add the edge to the adjacency list
        graph[v].push_back(u); // Since it's an undirected graph, add the reverse edge as well
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false; // Initialize the visited array
    }

    std::cout << "Depth First Search (DFS) traversal: ";
    dfs(start); // Perform DFS traversal starting from the given start node
    std::cout << std::endl;

    return 0;
}
