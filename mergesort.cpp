#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

void merge(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int* L = new int[n1 + 1];
    int* R = new int[n2 + 1];

    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[q + 1 + j];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;

    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main() {
    int sizes[10] = {1000, 5000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000};
    int runs = 10;

    srand(time(0));
    cout << "UEM24135 CODE FOR MERGE SORT\n;
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
            mergeSort(temp, 0, n - 1);
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
