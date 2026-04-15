#include <iostream>
#include <chrono>
#include <cstring>
using namespace std;

void permutation(char current[], int n, int idx) {
    if (idx == n) {
        return;
    }
    current[idx] = '0';
    permutation(current, n, idx + 1);
    current[idx] = '1';
    permutation(current, n, idx + 1);
}

int main() {
    int testValues[10] = {5, 8, 10, 12, 14, 16, 18, 20, 21, 23};
    cout << "UEM24135 CODE FOR PERMUTATION GENERATOR OF Binary STRING\n";
    cout << "String Length | Average Time (microseconds)\n";
    cout << "--------------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = testValues[i];

        double totalTime = 0.0;

        for (int iter = 0; iter < 10; iter++) {
            char current[30];
            memset(current, '0', n);
            current[n] = '\0';

            auto start = chrono::high_resolution_clock::now();
            permutation(current, n, 0);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, micro> duration = end - start;
            totalTime += duration.count();
        }

        double avgTime = totalTime / 10.0;
        cout << n << " | " << avgTime << " microseconds\n";
    }

    return 0;
}
