#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int testValues[10] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    int runs = 10;

    srand(time(0));
    cout << "UEM243135 Code for Insertion Sort Worst Case\n";
    cout << "Array Size | Average Time (microseconds)\n";
    cout << "------------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = testValues[i];

        int* original = new int[n];
        for (int k = 0; k < n; k++) {
        original[k] = n - k;  
        }

        double totalTime = 0.0;

        for (int r = 0; r < runs; r++) {

            int* temp = new int[n];
            for (int k = 0; k < n; k++) {
                temp[k] = original[k];
            }

            auto start = chrono::high_resolution_clock::now();
            insertionSort(temp, n);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, micro> duration = end - start;
            totalTime += duration.count();

            delete[] temp;
        }

        double avgTime = totalTime / runs;
        cout << n << "      | " << avgTime << " microseconds\n";

        delete[] original;
    }

    return 0;
}
