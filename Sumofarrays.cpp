#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

int sumOfArray(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int testValues[10] = {1000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
    int runs = 10000;

    srand(time(0));
    cout << "UEM243135 Code for Sum of arrays\n";
    cout << "Array Size | Average Time (microseconds)\n";
    cout << "------------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = testValues[i];

        int* arr = new int[n];
        for (int k = 0; k < n; k++) {
            arr[k] = rand() % 1000 + 1;
        }

        double dummy = 0;
        auto start = chrono::high_resolution_clock::now();
        for (int r = 0; r < runs; r++) {
            dummy += sumOfArray(arr, n);
        }
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, micro> duration = end - start;
        double avgTime = duration.count() / runs;

        cout << n << "      | " << avgTime << " microseconds\n";

        delete[] arr;
    }

    return 0;
}
