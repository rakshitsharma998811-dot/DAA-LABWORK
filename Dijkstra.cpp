#include <iostream>
#include <chrono>
#include <climits>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAXN = 505;
const int MAXE = 10005;

struct Edge {
    int to, weight, next;
} edges[MAXN][MAXE];

int edgeCount[MAXN];

struct HeapNode {
    int dist, u;
    bool operator>(const HeapNode &o) const { return dist > o.dist; }
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
            if (l < sz && data[l] > data[smallest] == false && data[smallest] > data[l]) smallest = l;
            if (r < sz && data[smallest] > data[r]) smallest = r;
            if (smallest == i) break;
            swap(data[i], data[smallest]);
            i = smallest;
        }
    }

    bool empty() { return sz == 0; }
};

int dist[MAXN];

void dijkstra(int n, int source) {
    for (int i = 0; i < n; i++) dist[i] = INT_MAX;
    MinHeap pq;
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        HeapNode top = pq.top(); pq.pop();
        int d = top.dist, u = top.u;
        if (d != dist[u]) continue;

        for (int i = 0; i < edgeCount[u]; i++) {
            int v = edges[u][i].to;
            int w = edges[u][i].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

void addEdge(int u, int v, int w) {
    edges[u][edgeCount[u]++] = {v, w, 0};
    edges[v][edgeCount[v]++] = {u, w, 0};
}

double timings[10][10];
int testValues[10] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};

int main() {
    cout << "UEM243135 CODE FOR DIJKSTRA ALGORITHM" ;
    cout << "Dijkstra Algorithm - Time Analysis\n";

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
            dijkstra(n, 0);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, micro> duration = end - start;
            timings[i][iter] = duration.count();
            timeTaken += duration.count();
        }

        double avgTime = timeTaken / 10.0;
        cout << "Vertices: " << n << " | Average Time: " << avgTime << " microseconds\n";
    }
}
