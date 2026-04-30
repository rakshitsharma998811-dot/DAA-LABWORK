#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

/**
 * Traveling Salesperson Problem (TSP) using DP + Bitmasking
 * Complexity: O(2^n * n^2)
 */
int n = 4;
int dist[10][10] = { {0, 20, 42, 25}, 
                     {20, 0, 30, 34}, 
                     {42, 30, 0, 10}, 
                     {25, 34, 10, 0} };
int memo[1 << 10][10];

int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1) {
        return dist[pos][0];
    }
    if (memo[mask][pos] != -1) {
        return memo[mask][pos];
    }

    int ans = 1e9;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            ans = std::min(ans, newAns);
        }
    }
    return memo[mask][pos] = ans;
}

int main() {
    std::memset(memo, -1, sizeof(memo));
    std::cout << "The minimum cost is " << tsp(1, 0) << std::endl;
    return 0;
}
