#include <iostream>
#include <chrono>
#include <climits>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAXN = 505;
const int MAXE = 10005;

struct Edge {
    int to, weight;
};

Edge graph[MAXN][MAXE];
int edgeCount[MAXN];

void addEdge(int u, int v, int w) {
    graph[u][edgeCount[u]++] = {v, w};
    graph[v][edgeCount[v]++] = {u, w};
}

// --- Min Heap ---
struct HeapNode {
    int weight, u;
    bool operator>(const HeapNode &o) const { return weight > o.weight; }
};

struct MinHeap {
    HeapNode data[MAXE];
    int sz = 0;

    void push(HeapNode x) {
        data[sz++] = x;
        int i = sz - 1;
        while (i > 0) {
            int p = (i - 1) / 2;
            if (data[p] > data[i]) { swap(data[p], data[i]); i = p; }
            else break;
        }
    }

    HeapNode top() { return data[0]; }

    void pop() {
        data[0] = data[--sz];
        int i = 0;
        while (true) {
            int l = 2*i+1, r = 2*i+2, smallest = i;
            if (l < sz && data[smallest] > data[l]) smallest = l;
            if (r < sz && data[smallest] > data[r]) smallest = r;
            if (smallest == i) break;
            swap(data[i], data[smallest]);
            i = smallest;
        }
    }

    bool empty() { return sz == 0; }
};

bool visited[MAXN];

int prims(int n) {
    for (int i = 0; i < n; i++) visited[i] = false;

    MinHeap pq;
    pq.push({0, 0});
    int minCost = 0;

    while (!pq.empty()) {
        int weight = pq.top().weight;
        int u      = pq.top().u;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        minCost += weight;

        for (int i = 0; i < edgeCount[u]; i++) {
            int v = graph[u][i].to;
            int w = graph[u][i].weight;
            if (!visited[v])
                pq.push({w, v});
        }
    }
    return minCost;
}

double timings[10][10];
int testValues[10] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};

int main() {
    cout < "UEM243135 CODE FOR PRIMS ALGORITHM\n";
    cout << "Prims Algorithm - Time Analysis\n";

    for (int i = 0; i < 10; i++) {
        int n = testValues[i];

        for (int j = 0; j < n; j++) edgeCount[j] = 0;

        srand(time(0) + i);
      
        for (int j = 0; j < n - 1; j++)
            addEdge(j, j + 1, rand() % 100 + 1);

        int extraEdges = 2 * n;
        for (int j = 0; j < extraEdges; j++) {
            int u = rand() % n;
            int v = rand() % n;
            if (u != v)
                addEdge(u, v, rand() % 100 + 1);
        }

        double timeTaken = 0.0;
        for (int iter = 0; iter < 10; iter++) {
            auto start = chrono::high_resolution_clock::now();
            int minCost = prims(n);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, micro> duration = end - start;
            timings[i][iter] = duration.count();
            timeTaken += duration.count();
        }

        double avgTime = timeTaken / 10.0;
        cout << "Vertices: " << n << " | Average Time: " << avgTime << " microseconds\n";
    }
}
