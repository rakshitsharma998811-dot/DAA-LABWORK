#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

int findMissingNumber(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] - arr[i-1] != 1) {
            return arr[i-1] + 1;
        }
    }
    return arr[n-1] + 1;
}

int main() {
    int testValues[10] = {1000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
    int runs = 10000;

    srand(time(0));
    cout << "UEM243135 CODE FOR Missing Number\n";
    cout << "Array Size | Average Time (microseconds)\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = testValues[i];

        int* arr = new int[n];

        int missing = n;
        int idx = 0;
        for (int k = 1; k <= n + 1; k++) {
            if (k != missing) {
                arr[idx++] = k;
            }
        }

        double dummy = 0;
        auto start = chrono::high_resolution_clock::now();
        for (int r = 0; r < runs; r++) {
            dummy += findMissingNumber(arr, n);
        }
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, micro> duration = end - start;
        double avgTime = duration.count() / runs;

        cout << n << "      | " << avgTime << " microseconds\n";

        delete[] arr;
    }

    return 0;
}
