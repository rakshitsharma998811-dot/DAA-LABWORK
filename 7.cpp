#include <iostream>
using namespace std;

int main() {
    int n, m;
    cout << "Enter size of array: ";
    cin >> n;

    int arr[n];
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter m: ";
    cin >> m;

    bool found = false;
    for (int i = 0; i <= n - m; i++) {
        bool consecutive = true;
        for (int j = 0; j < m - 1; j++) {
            if (arr[i + j + 1] != arr[i + j] + 1) {
                consecutive = false;
                break;
            }
        }
        if (consecutive) {
            found = true;
            break;
        }
    }

    if (found)
        cout << "m consecutive numbers found";
    else
        cout << "m consecutive numbers not found";

    return 0;
}
