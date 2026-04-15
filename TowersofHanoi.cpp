#include <iostream>
#include <chrono>
using namespace std;

void towerOfHanoi(int n, char from, char to, char aux) {
    if (n == 0) return;
    towerOfHanoi(n - 1, from, aux, to);
    // cout << "Move disk " << n << " from " << from << " to " << to << "\n";
    towerOfHanoi(n - 1, aux, to, from);
}

int main() {
    int testValues[10] = {5, 8, 10, 12, 14, 16, 18, 20, 22, 24};
    cout << "UEM243135 Code for Towers of Hanoi\n;
    cout << "Disks | Average Time (microseconds)\n";
    cout << "-------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = testValues[i];

        double totalTime = 0.0;

        for (int iter = 0; iter < 10; iter++) {
            auto start = chrono::high_resolution_clock::now();
            towerOfHanoi(n, 'A', 'C', 'B');
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, micro> duration = end - start;
            totalTime += duration.count();
        }

        double avgTime = totalTime / 10.0;
        cout << n << "    | " << avgTime << " microseconds\n";
    }

    return 0;
}
