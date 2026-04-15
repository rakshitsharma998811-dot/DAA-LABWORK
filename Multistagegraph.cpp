#include <iostream>
#include <climits>   // for INT_MAX
using namespace std;

// ── Constants ──────────────────────────────────────────────
const int MAX_V = 50;   // maximum vertices
const int MAX_E = 200;  // maximum edges
const int INF   = INT_MAX / 2;

struct Edge {
    int from, to, cost;
};

// ── Global data ────────────────────────────────────────────
int  n, e;                 
Edge edges[MAX_E];          
int  cost[MAX_V][MAX_V];     
int  stage[MAX_V];          
int  numStages;             
int  stageCount[MAX_V];     
int  verticesInStage[MAX_V][MAX_V]; 
void buildMatrix() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (i == j) ? 0 : INF;

    for (int k = 0; k < e; k++)
        cost[edges[k].from][edges[k].to] = edges[k].cost;
}

void assignStages() {
    int dist[MAX_V];
    for (int i = 0; i < n; i++) dist[i] = -1;
    dist[0] = 0;

    for (int u = 0; u < n; u++) {
        if (dist[u] == -1) continue;
        for (int v = 0; v < n; v++) {
            if (cost[u][v] != INF && v != u) {
                if (dist[v] < dist[u] + 1)
                    dist[v] = dist[u] + 1;
            }
        }
    }

    numStages = dist[n - 1] + 1;

    for (int i = 0; i < n; i++)
        stage[i] = (dist[i] == -1) ? 0 : dist[i];

    for (int s = 0; s < numStages; s++) stageCount[s] = 0;
    for (int i = 0; i < n; i++) {
        int s = stage[i];
        verticesInStage[s][stageCount[s]++] = i;
    }
}

void solveDP(int cost_dp[], int next[]) {
    for (int i = 0; i < n; i++) cost_dp[i] = INF;
    for (int i = 0; i < n; i++) next[i]    = -1;

    cost_dp[n - 1] = 0;  

    for (int s = numStages - 2; s >= 0; s--) {
        for (int ki = 0; ki < stageCount[s]; ki++) {
            int u = verticesInStage[s][ki];
            for (int v = 0; v < n; v++) {
                if (cost[u][v] != INF && cost_dp[v] != INF) {
                    int total = cost[u][v] + cost_dp[v];
                    if (total < cost_dp[u]) {
                        cost_dp[u] = total;
                        next[u]    = v;
                    }
                }
            }
        }
    }
}

void printPath(int next[]) {
    cout << "\n  Path  : ";
    int cur = 0;
    while (cur != -1) {
        cout << cur;
        if (next[cur] != -1) cout << " --> ";
        cur = next[cur];
    }
    cout << endl;
}

void displayStageInfo() {
    cout << "\n========================================\n";
    cout << "         STAGE INFORMATION\n";
    cout << "========================================\n";
    cout << "  Total Stages   : " << numStages << "\n";
    cout << "  Total Vertices : " << n         << "\n";
    cout << "  Total Edges    : " << e         << "\n\n";

    for (int s = 0; s < numStages; s++) {
        cout << "  Stage " << s + 1 << " : "
             << stageCount[s];
        if (stageCount[s] == 1) cout << " vertex ";
        else                    cout << " vertices";
        cout << "  { ";
        for (int k = 0; k < stageCount[s]; k++) {
            cout << verticesInStage[s][k];
            if (k < stageCount[s] - 1) cout << ", ";
        }
        cout << " }\n";
    }
}

void takeInput() {
    
    cout << " UEM243135 CODE FOR MULTISTAGE GRAPH - MIN COST PATH   \n";

    cout << "  Enter number of vertices : ";
    cin  >> n;
    if (n < 2) { cout << "  Need at least 2 vertices!\n"; exit(1); }

    cout << "  Enter number of edges    : ";
    cin  >> e;
    if (e < 1) { cout << "  Need at least 1 edge!\n"; exit(1); }

    cout << "\n  NOTE: Vertices are numbered 0 to " << n - 1 << "\n";
    cout << "        Source = 0,  Destination = " << n - 1 << "\n\n";

    cout << "  Enter each edge as:  <from>  <to>  <cost>\n";
    cout << "  ─────────────────────────────────────────\n";

    for (int k = 0; k < e; k++) {
        cout << "  Edge " << k + 1 << " : ";
        cin  >> edges[k].from >> edges[k].to >> edges[k].cost;

        if (edges[k].from < 0 || edges[k].from >= n ||
            edges[k].to   < 0 || edges[k].to   >= n) {
            cout << "  Invalid vertex number! Must be 0.." << n-1 << "\n";
            k--;   // re-enter
        }
    }
}

int main() {
    takeInput();
    buildMatrix();
    assignStages();
    displayStageInfo();

    int cost_dp[MAX_V], next[MAX_V];
    solveDP(cost_dp, next);

    cout << "\n========================================\n";
    cout << "         MINIMUM COST RESULT\n";
    cout << "========================================\n";

    if (cost_dp[0] == INF) {
        cout << "  No path exists from 0 to " << n - 1 << "!\n";
    } else {
        cout << "  Source      : 0\n";
        cout << "  Destination : " << n - 1 << "\n";
        cout << "  Min Cost    : " << cost_dp[0] << "\n";
        printPath(next);
    }

    cout << "========================================\n";
    return 0;
}
