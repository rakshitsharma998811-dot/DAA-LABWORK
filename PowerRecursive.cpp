#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

long long powerRecursive(int x, int n) {
    if (n == 0) return 1;
    long long half = powerRecursive(x, n / 2);
    if (n % 2 == 0) {
        return half * half;
    } else {
        return x * half * half;
    }
}

int main() {
    int testValues[10] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    int runs = 10000;

    srand(time(0));
    int x = rand() % 9 + 2;
    cout << "UEM24135 CODE FOR Recursive Power Function\n";
    cout << "Base x = " << x << "\n";
    cout << "Exponent | Average Time (microseconds)\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = testValues[i];

        double dummy = 0;
        auto start = chrono::high_resolution_clock::now();
        for (int r = 0; r < runs; r++) {
            dummy += powerRecursive(x, n);
        }
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, micro> duration = end - start;
        double avgTime = duration.count() / runs;

        cout << n << "      | " << avgTime << " microseconds\n";
    }

    return 0;
}
