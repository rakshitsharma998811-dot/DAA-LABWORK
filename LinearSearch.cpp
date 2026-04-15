#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

int main() {
    int testValues[10] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    int runs = 10000;

    srand(time(0));
    cout << "UEM243135 CODE FOR LINEAR SEARCH\n"
    cout << "Size  | Average Time (microseconds)\n";
    cout << "------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = testValues[i];

        int* arr = new int[n];
        for (int k = 0; k < n; k++) {
            arr[k] = rand() % 10000 + 1;
        }

        int target = -1;

        double dummy = 0;
        auto start = chrono::high_resolution_clock::now();
        for (int r = 0; r < runs; r++) {
            dummy += linearSearch(arr, n, target);
        }
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, micro> duration = end - start;
        double avgTime = duration.count() / runs;

        cout << n << "   | " << avgTime << " microseconds\n";

        delete[] arr;
    }

    return 0;
}
