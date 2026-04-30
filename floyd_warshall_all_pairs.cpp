#include <iostream>
#include <vector>

/**
 * Floyd-Warshall All Pairs Shortest Path Algorithm
 * Complexity: O(V^3)
 */
#define INF 99999

void floydWarshall(int V, std::vector<std::vector<int>>& graph) {
    std::vector<std::vector<int>> dist = graph;

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    std::cout << "Shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) std::cout << "INF ";
            else std::cout << dist[i][j] << "   ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int V = 4;
    std::vector<std::vector<int>> graph = { {0, 5, INF, 10},
                                            {INF, 0, 3, INF},
                                            {INF, INF, 0, 1},
                                            {INF, INF, INF, 0} };
    floydWarshall(V, graph);
    return 0;
}
