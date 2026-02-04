#include <iostream>
using namespace std;

int main() {
    int n, x;
    cout << "Enter degree of polynomial: ";
    cin >> n;

    int a[n + 1];
    cout << "Enter coefficients:\n";
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
    }

    cout << "Enter value of x: ";
    cin >> x;

    int result = a[0];
    for (int i = 1; i <= n; i++) {
        result = result * x + a[i];
    }

    cout << "Polynomial value = " << result;
    return 0;
}
