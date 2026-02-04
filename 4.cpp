#include <iostream>
using namespace std;

int power(int x, int n) {
    if (n == 0)
        return 1;
    return x * power(x, n - 1);
}

int main() {
    int x, n;
    cout << "Enter x and n: ";
    cin >> x >> n;

    cout << "Result = " << power(x, n);
    return 0;
}
