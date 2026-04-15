#include <iostream>
using namespace std;

int adj[100][100];
int visited[100];    
int n;
bool hasCycle = false;

void dfs(int node) {
    visited[node] = 1;  

    for (int v = 0; v < n; v++) {
        if (adj[node][v] != 0) {
            if (visited[v] == 1) {
              
                hasCycle = true;
                return;
            }
            if (visited[v] == 0) {
                dfs(v);
            }
        }
    }

    visited[node] = 2;  
}

int main() {
    cout << "UEM243135 Code for CycleDetection in Graph"/n"
    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter adjacency matrix (0 = no edge, 1 = edge):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> adj[i][j];

    for (int i = 0; i < n; i++)
        if (visited[i] == 0)
            dfs(i);

    if (hasCycle)
        cout << "\nCycle DETECTED — This graph is NOT a DAG.\n";
    else
        cout << "\nNo Cycle found — This graph is a valid DAG.\n";

    return 0;
}
