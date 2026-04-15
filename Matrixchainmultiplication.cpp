#include <bits/stdc++.h>
using namespace std;

int m[100][100];  // cost table
int s[100][100];  // split point table

void matrixChain(vector<int>& p, int n) {

    // Single matrix = 0 cost (base case)
    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    // len = chain length (how many matrices in current subproblem)
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            m[i][j] = INT_MAX;

            // Try every split point k
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;  // store best split point
                }
            }
        }
    }
}

void printParenthesis(int i, int j) {
    if (i == j) {
        cout << "M" << i;
        return;
    }
    cout << "(";
    printParenthesis(i, s[i][j]);        // left part
    printParenthesis(s[i][j] + 1, j);   // right part
    cout << ")";
}

int main() {
    // M1 = 30x35, M2 = 35x15, M3 = 15x5, M4 = 5x10, M5 = 10x20, M6 = 20x25
    vector<int> p = {300, 355, 155, 555, 100, 200, 250};
    int n = p.size() - 1;  // 6 matrices

    matrixChain(p, n);

    cout << "Minimum Cost = " << m[1][n] << endl;
    cout << "Optimal Parenthesization = ";
    printParenthesis(1, n);
    cout << endl;

    return 0;
}
