#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(int A[], int p, int q) {
    int x = A[p];     
    int i = p;       

    for (int j = p + 1; j <= q; j++) {   
        if (A[j] <= x) {                 
            i = i + 1;                  
            swap(A[i], A[j]);         
        }
    }
    swap(A[i], A[p]);  
    return i;         
}

void quickSort(int A[], int p, int q) {
    if (p < q) {
        int pivot = partition(A, p, q);
        quickSort(A, p, pivot - 1);
        quickSort(A, pivot + 1, q);
    }
}

int main() {
    int sizes[10] = {1000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
    int runs = 10;

    srand(time(0));
    cout << "UEM243135 Code for QUICK SORT\n;
    cout << "Array Size | Average Time (microseconds)\n";
    cout << "------------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = sizes[i];

        int* orig = new int[n];
        for (int k = 0; k < n; k++)
            orig[k] = rand() % 1000 + 1; 

        double total = 0.0;

        for (int r = 0; r < runs; r++) {
            int* temp = new int[n];
            for (int k = 0; k < n; k++)
                temp[k] = orig[k];

            auto start = chrono::high_resolution_clock::now();
            quickSort(temp, 0, n - 1);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, micro> dur = end - start;
            total += dur.count();

            delete[] temp;
        }

        double avg = total / runs;
        cout << n << "      | " << avg << " microseconds\n";

        delete[] orig;
    }

    return 0;
}
