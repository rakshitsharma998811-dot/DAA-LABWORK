#include <iostream>
#include <vector>
#include <climits>

/**
 * Matrix Chain Multiplication using Dynamic Programming
 * Complexity: O(n^3)
 */
int matrixChainOrder(const std::vector<int>& p) {
    int n = p.size();
    std::vector<std::vector<int>> m(n, std::vector<int>(n, 0));

    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }
    return m[1][n - 1];
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4}; // Matrix dimensions: 1x2, 2x3, 3x4
    std::cout << "Minimum multiplications is " << matrixChainOrder(arr) << std::endl;
    return 0;
}
