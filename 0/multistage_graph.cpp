#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

/**
 * Shortest path in a Multistage Graph using Dynamic Programming
 * Complexity: O(V^2)
 */
#define INF INT_MAX

int shortestPath(int n, const std::vector<std::vector<int>>& graph) {
    std::vector<int> dist(n);
    dist[n - 1] = 0;

    for (int i = n - 2; i >= 0; i--) {
        dist[i] = INF;
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != INF) {
                dist[i] = std::min(dist[i], graph[i][j] + dist[j]);
            }
        }
    }
    return dist[0];
}

int main() {
    int n = 8; // Number of vertices
    std::vector<std::vector<int>> graph(n, std::vector<int>(n, INF));
    
    // Example graph setup
    graph[0][1] = 1; graph[0][2] = 2; graph[0][3] = 5;
    graph[1][4] = 4; graph[1][5] = 11;
    graph[2][4] = 9; graph[2][5] = 5;
    graph[3][6] = 2;
    graph[4][7] = 18;
    graph[5][7] = 2;
    graph[6][7] = 5;

    std::cout << "Shortest distance in multistage graph: " << shortestPath(n, graph) << std::endl;
    return 0;
}
