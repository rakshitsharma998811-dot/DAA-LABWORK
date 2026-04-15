#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

double hornersRule(double coef[], int n, double x) {
    double result = coef[n];
    for (int i = n - 1; i >= 0; i--) {
        result = coef[i] + x * result;
    }
    return result;
}

int main() {
    int testValues[10] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    double x = 0.5;
    int runs = 10000;

    srand(time(0));
    cout << "UEM243135 CODE FOR HORNERS RULE\n";
    cout << "Degree | Average Time (microseconds)\n";
    cout << "------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = testValues[i];

        double* coef = new double[n + 1];
        for (int k = 0; k <= n; k++) {
            coef[k] = rand() % 10 + 1;
        }

        double dummy = 0;
        auto start = chrono::high_resolution_clock::now();
        for (int r = 0; r < runs; r++) {
            dummy += hornersRule(coef, n, x);
        }
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, micro> duration = end - start;
        double avgTime = duration.count() / runs;

        cout << n << "   | " << avgTime << " microseconds\n";

        delete[] coef;
    }

    return 0;
}
