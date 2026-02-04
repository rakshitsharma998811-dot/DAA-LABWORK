#include <iostream>
using namespace std;

int main() {
    int a, b;

    cout << "A B AND OR NOT(A)\n";
    for (a = 0; a <= 1; a++) {
        for (b = 0; b <= 1; b++) {
            cout << a << " " << b << "  "
                 << (a & b) << "   "
                 << (a | b) << "    "
                 << (!a) << endl;
        }
    }
    return 0;
}
