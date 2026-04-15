#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int binarySearch(int arr[], int low, int high, int target) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (arr[mid] == target) return mid;
    else if (arr[mid] > target) return binarySearch(arr, low, mid - 1, target);
    else return binarySearch(arr, mid + 1, high, target);
}

int main() {
    int testValues[10] = {1000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
    int runs = 10000;

    srand(time(0));
    cout << "UEM243135 Code for Binary Search\n";
    cout << "Array Size | Average Time (microseconds)\n";
    cout << "------------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = testValues[i];

        int* arr = new int[n];
        for (int k = 0; k < n; k++) {
            arr[k] = k + 1;  
        }
        
        int target = -1;

        double dummy = 0;
        auto start = chrono::high_resolution_clock::now();
        for (int r = 0; r < runs; r++) {
            dummy += binarySearch(arr, 0, n - 1, target);
        }
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, micro> duration = end - start;
        double avgTime = duration.count() / runs;

        cout << n << "      | " << avgTime << " microseconds\n";

        delete[] arr;
    }

    return 0;
}
